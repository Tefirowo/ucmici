/*  Esta es una recreacion del programa ELENA (basado en la ELIZA de Joseph Weizenbaum de 1966).
    Traducido y adaptado al espanol con parser de archivos externos completo.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <cassert>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include <deque>
#include <cctype>
#include <thread>
#include <array>
#include <cstdint>
#include <locale>
#include <iomanip>

using stringlist = std::deque<std::string>;

std::ostream & operator<<(std::ostream & os, const stringlist & list)
{
    os << '(';
    for (auto s : list)
        os << '"' << s << '"' << ' ';
    os << ')';
    return os;
}

template<typename T>
auto pop_front(T & container)
{
    auto v(container.front());
    container.pop_front();
    return v;
}

template<>
auto pop_front(std::string & container)
{
    auto v(container.front());
    container.erase(0, 1);
    return v;
}

std::string to_upper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return static_cast<char>(std::toupper(c)); }
    );
    return s;
}

stringlist split(const std::string & s)
{
    stringlist result;
    std::string word;
    for (auto ch : s) {
        if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
            if (!word.empty()) {
                result.push_back(word);
                word.clear();
            }
        }
        else
            word.push_back(ch);
    }
    if (!word.empty())
        result.push_back(word);
    return result;
}

std::string join(const stringlist & words)
{
    std::string result;
    for (const auto & word : words) {
        if (!word.empty()) {
            if (!result.empty())
                result += ' ';
            result += word;
        }
    }
    return result;
}

namespace elenalogic {

using tagmap = std::map<std::string, stringlist>;

constexpr unsigned char hollerith_undefined = 0xFFu;

const std::array<unsigned char, 256> hollerith_encoding{ []{
    static constexpr unsigned char bcd[64] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 0, '=', '\'', 0, 0, 0,
        '+', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 0, '.', ')',  0, 0, 0,
        '-', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 0, '$', '*',  0, 0, 0,
        ' ', '/', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 0, ',', '(',  0, 0, 0
    };
    std::array<unsigned char, 256> to_bcd;
    to_bcd.fill(hollerith_undefined);
    for (unsigned char c = 0; c < 64; ++c)
        if (bcd[c])
            to_bcd[bcd[c]] = c;
    return to_bcd;
}() };

bool hollerith_defined(char c)
{
    const unsigned char uc{ static_cast<unsigned char>(c) };
    return hollerith_encoding[uc] != hollerith_undefined;
}

std::u32string utf8_to_utf32(const std::string & utf8_string)
{
    std::u32string s;
    const size_t len = utf8_string.size();
    for (size_t i = 0; i < len; ) {
        uint32_t c32 = 0;
        size_t trailing = 0;
        unsigned char c = utf8_string[i++];
        if ((c & 0x80) == 0x00) {
            c32 = static_cast<uint32_t>(c);
        } else if ((c & 0xE0) == 0xC0) {
            c32 = static_cast<uint32_t>(c - 0xC0);
            trailing = 1;
        } else if ((c & 0xF0) == 0xE0) {
            c32 = static_cast<uint32_t>(c - 0xE0);
            trailing = 2;
        } else if ((c & 0xF8) == 0xF0) {
            c32 = static_cast<uint32_t>(c - 0xF0);
            trailing = 3;
        } else {
            c32 = static_cast<uint32_t>(c);
        }
        while (trailing-- && i < len) {
            c = utf8_string[i++];
            c32 <<= 6;
            c32 |= static_cast<uint32_t>(c & 0x3F);
        }
        s += c32;
    }
    return s;
}

std::string utf32_to_utf8(uint32_t c32)
{
    std::string result;
    if (c32 <= 0x7F) {
        result += static_cast<char>(c32);
    } else {
        result += static_cast<char>(0x3F);
    }
    return result;
}

uint32_t uppercase_utf32(uint32_t c32)
{
    if (c32 >= 'a' && c32 <= 'z')
        return c32 - ('a' - 'A');
    return c32;
}

std::string elena_uppercase(const std::string & utf8_string)
{
    std::string result;
    std::u32string utf32(utf8_to_utf32(utf8_string));
    for (auto ch : utf32) {
        const uint32_t c32 = static_cast<uint32_t>(ch);
        switch (c32) {
        case 0x0021:
        case 0x003F:
            result += '.';
            break;
        case 0x00A1:
        case 0x00BF:
            result += ' ';
            break;
        case 0x003A:
        case 0x003B:
        case 0x2013:
        case 0x2014:
            result += ',';
            break;
        default:
            result += utf32_to_utf8(uppercase_utf32(c32));
            break;
        }
    }
    return result;
}

int to_int(const std::string & s)
{
    int result = 0;
    for (auto c : s) {
        if (std::isdigit(c))
            result = 10 * result + c - '0';
        else
            return -1;
    }
    return result;
}

bool inlist(const std::string & word, std::string wordlist, const tagmap & tags)
{
    assert(!word.empty());
    if (wordlist.back() == ')')
        wordlist.pop_back();
    const char * cp = wordlist.data();
    if (*cp == '(')
        ++cp;
    while (*cp == ' ')
        ++cp;
    if (*cp == '*') {
        ++cp;
        const stringlist s{split(std::string(cp))};
        return std::find(s.begin(), s.end(), word) != s.end();
    }
    else if (*cp == '/') {
        ++cp;
        const auto taglist{split(std::string(cp))};
        for (const auto & tag : taglist) {
            const auto t = tags.find(tag);
            if (t != tags.end()) {
                const stringlist & s{t->second};
                if (std::find(s.begin(), s.end(), word) != s.end())
                    return true;
            }
        }
    }
    return false;
}

bool match(const tagmap & tags, const stringlist & pattern,
        const stringlist & words, stringlist & matching_components)
{
    matching_components.clear();
    struct variable_length_wildcard_record {
        int pattern_index;
        int words_index;
        int length;
        variable_length_wildcard_record(int p = 0, int w = 0, int l = 0)
            : pattern_index(p), words_index(w), length(l) {}
    };
    std::deque<variable_length_wildcard_record> wildcards;
    std::vector<std::string> pat_array{ pattern.begin(), pattern.end() };
    std::vector<std::string> word_array{ words.begin(), words.end() };

    for (int p = 0, w = 0;;) {
        if (p < pat_array.size()) {
            int n = to_int(pat_array[p]);
            if (n == 0) {
                wildcards.emplace_back(p++, w, 0);
                continue;
            }
            if (w < word_array.size()) {
                if (n > 0) {
                    ++p;
                    w += n;
                    if (w <= word_array.size())
                        continue;
                }
                else {
                    if (pat_array[p].front() == '(') {
                        if (inlist(word_array[w], pat_array[p], tags)) {
                            p++;
                            w++;
                            continue;
                        }
                    }
                    else if (pat_array[p] == word_array[w]) {
                        p++;
                        w++;
                        continue;
                    }
                }
            }
        }
        else if (w == word_array.size())
            break;

        for (;;) {
            if (wildcards.empty())
                return false;
            auto & current_wildcard = wildcards.back();
            current_wildcard.length++;
            if (current_wildcard.words_index + current_wildcard.length <= word_array.size())
                break;
            wildcards.pop_back();
        }
        p = wildcards.back().pattern_index + 1;
        w = wildcards.back().words_index + wildcards.back().length;
    }

    for (int p = 0, w = 0; p < pat_array.size(); ++p) {
        int part_length = 1;
        int n = to_int(pat_array[p]);
        if (n == 0) {
            assert(!wildcards.empty());
            part_length = wildcards.front().length;
            wildcards.pop_front();
        }
        else if (n > 1)
            part_length = n;
        stringlist part;
        for (int i = 0; i < part_length; ++i)
            part.emplace_back(word_array[w++]);
        matching_components.emplace_back(join(part));
    }
    return true;
}

stringlist reassemble(const stringlist & reassembly_rule, const stringlist & components)
{
    stringlist result;
    for (const auto & r : reassembly_rule) {
        int n = to_int(r);
        if (n < 0)
            result.push_back(r);
        else if (n == 0 || static_cast<size_t>(n) > components.size()) {
            result.emplace_back("HMMM");
        }
        else {
            const stringlist expanded{split(components[n - 1])};
            result.insert(result.end(), expanded.begin(), expanded.end());
        }
    }
    return result;
}

uint_least64_t last_chunk_as_bcd(std::string s)
{
    uint_least64_t result = 0;
    auto append = [&](char c) {
        result <<= 6;
        if (hollerith_defined(c)) {
            const unsigned char uc{ static_cast<unsigned char>(c) };
            result |= hollerith_encoding[uc];
        } else {
            result |= static_cast<unsigned char>(c & 0x3F);
        }
    };
    int count = 0;
    if (!s.empty()) {
        for (auto c = std::next(s.begin(), ((s.length() - 1) / 6) * 6);
                c != std::end(s); ++c, ++count) {
            append(*c);
        }
    }
    while (count++ < 6)
        append(' ');
    return result;
}

int hash(uint_least64_t d, int n)
{
    assert(0 <= n && n <= 15);
    d &= 0x7FFFFFFFFULL;
    d *= d;
    d >>= 35 - n / 2;
    return d & (1ULL << n) - 1;
}

class rule_base {
public:
    rule_base() = default;
    rule_base(const std::string & keyword, const std::string & word_substitution, int precedence)
        : keyword_(keyword), word_substitution_(word_substitution), precedence_(precedence) {}
    virtual ~rule_base() = default;

    void set_keyword(const std::string & keyword) { keyword_ = keyword; }
    void add_transformation_rule(const stringlist & decomposition,
        const std::vector<stringlist> & reassembly_rules)
    {
        trans_.emplace_back(decomposition, reassembly_rules);
    }

    int precedence() const { return precedence_; }
    std::string keyword() const { return keyword_; }

    enum class action { inapplicable, complete, newkey, linkkey };

    virtual action apply_word_substitution(std::string & word)
    {
        if (word_substitution_.empty() || word != keyword_)
            return action::inapplicable;
        word = word_substitution_;
        return action::complete;
    }

    virtual std::string word_substitute(const std::string & word) const
    {
        if (word_substitution_.empty() || word != keyword_)
            return word;
        return word_substitution_;
    }

    virtual bool has_transformation() const { return false; }

    virtual action apply_transformation(stringlist & /*words*/,
        const tagmap & /*tags*/, std::string & /*link_keyword*/)
    {
        return action::inapplicable;
    }

    virtual stringlist dlist_tags() const { return stringlist(); }
    virtual std::string to_string() const = 0;

protected:
    std::string keyword_;
    std::string word_substitution_;
    int precedence_{ 0 };

    struct transform {
        stringlist decomposition;
        std::vector<stringlist> reassembly_rules;
        unsigned next_reassembly_rule{ 0 };
        transform() = default;
        transform(const stringlist & decomposition,
            const std::vector<stringlist> & reassembly_rules)
            : decomposition(decomposition), reassembly_rules(reassembly_rules) {}
    };
    std::vector<transform> trans_;
};

std::string rule_base::to_string() const { return std::string(); }

using rulemap = std::map<std::string, std::shared_ptr<rule_base>>;
const std::string special_rule_none{"zNONE"};

class rule_memory : public rule_base {
public:
    rule_memory() = default;
    explicit rule_memory(const std::string & keyword) : rule_base(keyword, "", 0) {}

    bool empty() const { return keyword_.empty() || trans_.empty(); }

    void create_memory(const std::string & keyword, const stringlist & words, const tagmap & tags)
    {
        if (keyword != keyword_)
            return;
        if (trans_.empty()) return;
        const auto & transformation = trans_[hash(last_chunk_as_bcd(words.back()), 2) % trans_.size()];
        stringlist constituents;
        if (!match(tags, transformation.decomposition, words, constituents))
            return;
        const auto new_memory{join(reassemble(transformation.reassembly_rules[0], constituents))};
        memories_.push_back(new_memory);
    }

    bool memory_exists() const { return !memories_.empty(); }

    std::string recall_memory() { return memories_.empty() ? "" : pop_front(memories_); }

    virtual std::string to_string() const override
    {
        std::string sexp("(MEMORIA ");
        sexp += keyword_;
        for (const auto & k : trans_) {
            sexp += "\n    (" + join(k.decomposition);
            sexp += " = " + join(k.reassembly_rules[0]) + ")";
        }
        sexp += ")\n";
        return sexp;
    }

    virtual void clear_trace() { trace_.str(""); }
    virtual std::string trace() const { return trace_.str(); }

private:
    stringlist memories_;
    std::stringstream trace_;
};

class rule_keyword : public rule_base {
public:
    rule_keyword() = default;
    rule_keyword(const std::string & keyword, const std::string & word_substitution,
        int precedence, const stringlist & tags, const std::string & link_keyword)
        : rule_base(keyword, word_substitution, precedence), tags_(tags), link_keyword_(link_keyword) {}

    stringlist dlist_tags() const { return tags_; }

    virtual bool has_transformation() const { return !trans_.empty() || !link_keyword_.empty(); }

    virtual std::string to_string() const override {
        return "( " + keyword_ + " )";
    }

    virtual action apply_transformation(stringlist & words, const tagmap & tags, std::string & link_keyword)
    {
        stringlist constituents;
        auto rule = trans_.begin();
        while (rule != trans_.end() && !match(tags, rule->decomposition, words, constituents))
            ++rule;
        if (rule == trans_.end()) {
            if (link_keyword_.empty())
                return action::inapplicable;
            link_keyword = link_keyword_;
            return action::linkkey;
        }

        stringlist& reassembly_rule = rule->reassembly_rules[rule->next_reassembly_rule];
        rule->next_reassembly_rule++;
        if (rule->next_reassembly_rule == rule->reassembly_rules.size())
            rule->next_reassembly_rule = 0;

        if (reassembly_rule.size() == 1 && reassembly_rule[0] == "NEWKEY")
            return action::newkey;

        if (reassembly_rule.size() == 2 && reassembly_rule[0].size() == 1 && reassembly_rule[0][0] == '=') {
            link_keyword = reassembly_rule[1];
            return action::linkkey;
        }

        words = reassemble(reassembly_rule, constituents);
        return action::complete;
    }

private:
    stringlist tags_;
    std::string link_keyword_;
};

tagmap collect_tags(const rulemap & rules)
{
    tagmap tags;
    for (const auto & tag : rules) {
        stringlist keyword_tags(tag.second->dlist_tags());
        for (auto t : keyword_tags) {
            if (t == "/") continue;
            if (t.size() > 1 && t.front() == '/') pop_front(t);
            tags[t].push_back(tag.second->keyword());
        }
    }
    return tags;
}

class elena {
public:
    elena(const rulemap & rules, std::shared_ptr<rule_memory> mem_rule)
        : rules_(rules), mem_rule_(mem_rule), tags_(collect_tags(rules_))
    {
        set_delimeters({ ",", ".", "PERO" });
    }

    void set_delimeters(const stringlist & delims)
    {
        delimiters_ = delims;
        punctuation_.clear();
        for (const auto & d : delims) {
            if (d.size() == 1) punctuation_ += d[0];
        }
    }

    std::string response(const std::string & input)
    {
        stringlist words(split_user_input(elena_uppercase(input), punctuation_));

        for (auto & w : words) {
            if (w == "ESTOY") w = "ESTAS";
            else if (w == "SOY") w = "ERES";
            else if (w == "TENGO") w = "TIENES";
            else if (w == "QUIERO") w = "QUIERES";
            else if (w == "SIENTO") w = "SIENTES";
        }

        limit_ = limit_ % 4 + 1;

        stringlist keystack;
        int top_rank = 0;
        for (auto word = words.begin(); word != words.end(); ) {
            if (delimiter(*word)) {
                if (keystack.empty()) {
                    ++word;
                    word = words.erase(words.begin(), word);
                    continue;
                } else {
                    word = words.erase(word, words.end());
                    break;
                }
            }

            const auto r = rules_.find(*word);
            if (r != rules_.end()) {
                const auto & rule = r->second;
                if (rule->has_transformation()) {
                    if (rule->precedence() > top_rank) {
                        keystack.push_front(*word);
                        top_rank = rule->precedence();
                    } else {
                        keystack.push_back(*word);
                    }
                }
                const std::string substitute(rule->word_substitute(*word));
                *word = substitute;
            }
            ++word;
        }

        if (keystack.empty()) {
            if (limit_ == 4 && mem_rule_->memory_exists()) {
                return mem_rule_->recall_memory();
            }
        }

        while (!keystack.empty()) {
            const std::string top_keyword = pop_front(keystack);
            auto r = rules_.find(top_keyword);
            if (r == rules_.end()) {
                return nomatch_msgs_[limit_ - 1];
            }
            auto rule = r->second;
            mem_rule_->create_memory(top_keyword, words, tags_);

            std::string link_keyword;
            auto act = rule->apply_transformation(words, tags_, link_keyword);

            if (act == rule_base::action::complete)
                return join(words);

            if (act == rule_base::action::inapplicable)
                return nomatch_msgs_[limit_ - 1];

            if (act == rule_base::action::linkkey)
                keystack.push_front(link_keyword);
            else if (keystack.empty())
                return nomatch_msgs_[limit_ - 1];
        }

        auto r_none = rules_.find(elenalogic::special_rule_none);
        if (r_none != rules_.end()) {
            std::string discard;
            r_none->second->apply_transformation(words, tags_, discard);
            return join(words);
        }

        return nomatch_msgs_[limit_ - 1];
    }

private:
    int limit_{ 1 };
    stringlist delimiters_;
    std::string punctuation_;
    bool delimiter(const std::string & s) const
    {
        return std::find(delimiters_.begin(), delimiters_.end(), s) != delimiters_.end();
    }
    rulemap rules_;
    std::shared_ptr<rule_memory> mem_rule_;
    const tagmap tags_;
    static const char * const nomatch_msgs_[4];

    stringlist split_user_input(const std::string & s, const std::string & punctuation)
    {
        stringlist result;
        std::string word;
        for (auto ch : s) {
            if (ch == ' ' || std::find(punctuation.begin(), punctuation.end(), ch) != punctuation.end()) {
                if (!word.empty()) {
                    result.push_back(word);
                    word.clear();
                }
                if (ch != ' ')
                    result.emplace_back(1, ch);
            }
            else
                word.push_back(ch);
        }
        if (!word.empty())
            result.push_back(word);
        return result;
    }
};

const char * const elena::nomatch_msgs_[4] = {
    "CONTINUE POR FAVOR",
    "HMMM",
    "SIGUE, POR FAVOR",
    "YA VEO"
};

} //namespace elenalogic


namespace elenascript {

struct script {
    std::string hello_message;
    elenalogic::rulemap rules;
    std::shared_ptr<elenalogic::rule_memory> mem_rule;
};

script parse_script(std::istream & is) {
    script sc;
    sc.mem_rule = std::make_shared<elenalogic::rule_memory>("MI");

    std::string line;
    std::string full_content;
    while (std::getline(is, line)) {
        size_t comment_pos = line.find(';');
        if (comment_pos != std::string::npos) {
            line = line.substr(0, comment_pos);
        }
        full_content += line + " ";
    }

    std::vector<std::string> tokens;
    std::string current_token;
    for (char c : full_content) {
        if (c == '(' || c == ')') {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
            tokens.push_back(std::string(1, c));
        } else if (std::isspace(static_cast<unsigned char>(c))) {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token.clear();
            }
        } else {
            current_token += c;
        }
    }
    if (!current_token.empty()) {
        tokens.push_back(current_token);
    }

    size_t idx = 0;
    auto peek = [&]() { return idx < tokens.size() ? tokens[idx] : ""; };
    auto consume = [&]() { return idx < tokens.size() ? tokens[idx++] : ""; };

    if (peek() == "(") {
        consume(); // (
        std::string hello;
        while (peek() != ")" && idx < tokens.size()) {
            hello += consume() + " ";
        }
        if (peek() == ")") consume();
        sc.hello_message = hello;
    }

    while (idx < tokens.size() && tokens[idx] != "INICIO") {
        idx++;
    }
    if (idx < tokens.size()) idx++;

    while (idx < tokens.size()) {
        if (consume() != "(") continue;

        std::string kw_or_mem = consume();
        if (kw_or_mem.empty()) break;

        if (kw_or_mem == "MEMORIA") {
            std::string mem_kw = consume();
            sc.mem_rule = std::make_shared<elenalogic::rule_memory>(mem_kw);
            while (peek() == "(") {
                consume(); // (
                stringlist decomp;
                while (peek() != "=" && peek() != ")" && idx < tokens.size()) {
                    decomp.push_back(consume());
                }
                if (peek() == "=") {
                    consume(); // =
                    stringlist reasm;
                    while (peek() != ")" && idx < tokens.size()) {
                        reasm.push_back(consume());
                    }
                    sc.mem_rule->add_transformation_rule(decomp, {reasm});
                }
                if (peek() == ")") consume();
            }
            if (peek() == ")") consume();
            continue;
        }

        int precedence = 0;
        std::string substitution = "";
        stringlist tags;
        std::vector<std::pair<stringlist, std::vector<stringlist>>> trans_rules;
        std::string link_keyword = "";

        if (peek() != "(" && peek() != "=" && peek() != ")") {
            std::string next_tok = consume();
            int p = elenalogic::to_int(next_tok);
            if (p >= 0) {
                precedence = p;
            }
        }

        if (peek() == "=") {
            consume();
            substitution = consume();
        }

        while (idx < tokens.size() && peek() != ")") {
            if (peek() == "=") {
                consume();
                link_keyword = consume();
                break;
            }
            if (peek() == "(") {
                consume();
                stringlist decomp;
                if (peek() == "(") {
                    consume();
                    while (peek() != ")" && idx < tokens.size()) {
                        decomp.push_back(consume());
                    }
                    if (peek() == ")") consume();
                } else {
                    while (peek() != "(" && peek() != ")" && idx < tokens.size()) {
                        decomp.push_back(consume());
                    }
                }

                std::vector<stringlist> reasms;
                while (peek() == "(" && idx < tokens.size()) {
                    consume();
                    stringlist reasm;
                    while (peek() != ")" && idx < tokens.size()) {
                        reasm.push_back(consume());
                    }
                    if (peek() == ")") consume();
                    reasms.push_back(reasm);
                }
                trans_rules.push_back({decomp, reasms});
                if (peek() == ")") consume();
            } else {
                consume();
            }
        }
        if (peek() == ")") consume();

        auto rule = std::make_shared<elenalogic::rule_keyword>(kw_or_mem, substitution, precedence, tags, link_keyword);
        for (auto & tr : trans_rules) {
            rule->add_transformation_rule(tr.first, tr.second);
        }
        sc.rules[kw_or_mem] = rule;
    }

    if (sc.rules.find(elenalogic::special_rule_none) == sc.rules.end()) {
        auto r_none = std::make_shared<elenalogic::rule_keyword>(elenalogic::special_rule_none, "", 0, stringlist{}, "");
        r_none->add_transformation_rule(stringlist{"0"}, {
            stringlist{"NO", "ESTOY", "SEGURA", "DE", "ENTENDERTE", "COMPLETAMENTE"},
            stringlist{"POR", "FAVOR,", "CONTINUA"},
            stringlist{"QUE", "TE", "SUGIERE", "ESO"}
        });
        sc.rules[elenalogic::special_rule_none] = r_none;
    }

    return sc;
}

} //namespace elenascript

int main(int argc, char* argv[]) {
    elenascript::script s;

    std::string archivo_reglas = (argc > 1) ? argv[1] : "reglas_elena.txt";
    std::ifstream archivo(archivo_reglas);

    if (archivo.is_open()) {
        std::cout << "[cargando reglas desde " << archivo_reglas << "...]\n";
        s = elenascript::parse_script(archivo);
    } else {
        std::cerr << "Aviso: No se pudo abrir '" << archivo_reglas << "'. Usando script interno basico por defecto.\n";
        std::stringstream ss("(HOLA. POR FAVOR, CUENTAME TU PROBLEMA)\nINICIO\n(HOLA ((0) (HOLA. ¿QUE TAL?)))\n()");
        s = elenascript::parse_script(ss);
    }

    if (!s.hello_message.empty()) {
        std::cout << "ELENA: " << s.hello_message << "\n";
    } else {
        std::cout << "ELENA: Hola, por favor cuentame tu problema.\n";
    }

    std::string user_input;
    elenalogic::elena elena_bot(s.rules, s.mem_rule);

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, user_input)) {
            break;
        }

        auto first = user_input.find_first_not_of(" \t\r\n");
        std::string trimmed = (first == std::string::npos) ? "" : user_input.substr(first, user_input.find_last_not_of(" \t\r\n") - first + 1);

        std::string upper_input = trimmed;
        std::transform(upper_input.begin(), upper_input.end(), upper_input.begin(), [](unsigned char c){ return std::toupper(c); });

        if (trimmed.empty() || upper_input == "CHAU") {
            std::cout << "ELENA: FUE UN PLACER HABLAR CONTIGO :b\n";
            break;
        }

        std::string bot_reply = elena_bot.response(user_input);
        std::cout << "ELENA: " << bot_reply << "\n";
    }

    return 0;
}
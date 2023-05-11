// Ozyegin University 2022-23 Spring Term CS409/509 Takehome Exam 1
// This exam is exactly the same for CS409 and CS509 students
// This exam is the same, but, Takehome 2 will have different questions tailored for
// undergrad and grad students.

// !!!!!!!!!! FILL-IN BELOW TWO LINES !!!!!!!!!!!!!!
// STUDENT NUMBER: ......
// STUDENT NAME: ........

// All the takehome exam 1 is in this file. There is no extra file for the exam.
// !!!!!!!!!! READ THIS FILE FULLY AND VERY CAREFULLY BEFORE STARTING YOUR SOLUTIONS. !!!!!!!!!!

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// THIS IS AN OPEN EXAM. YOU CAN USE GPT-4, ALL AVAILABLE LITERATURE, ETC.
// BUT YOU NEED TO SOLVE THE EXAM PERSONALLY YOURSELF.
// YOU CANNOT GET HELP FROM REAL PERSONS.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// YOU MIGHT BE SELECTED FOR AN ORAL EXAM AND BE WANTED TO MANIPULATE YOUR OWN SUBMITTED CODE.
// THIS IS PART OF THE SYLLABUS.
// ANY MAJOR FAILURE IN THE ORAL EXAM WILL CAUSE A DISCIPLINARY ACTION.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// In this exam, you will code a Regular Expression Matcher
// A regular expression (regex) is a sequence of characters that define a
// search pattern used to match and manipulate text.

// You are already provided a sample codebase below that supports basic RegexMatcher that supports:
// - single fixed character matching
// - single any character matching
//     (DOT) . character means match any character
// - character classes support:
//     [aDf] -> means match either a, D or f
//     [c-y] -> means match any character between c to y alpabetically: c, d, e, ..., x, y
//     [c-yA-C] -> means match any character between c to y or A to C: c, ..., x, y, A, B, C
//     [12c-e] -> 1, 2, c, d, e

// Now have a look at the code first, then start solving all the questions provided at the end.

#include <iostream>
#include <string>
#include <set>

using namespace std;

struct RegexMatcher {
    string pattern;

    RegexMatcher(const string& pattern) : pattern(pattern) { }

    auto parseCharacterClass(std::size_t start) const -> std::pair<set<char>, std::size_t>
    {
        set<char> char_class;
        std::size_t i = start;

        while (i < pattern.size() && pattern[i] != ']') {
            char c1 = pattern[i++];
            if (i < pattern.size() && pattern[i] == '-' && i + 1 < pattern.size()) {
                char c2 = pattern[i + 1];
                i += 2;
                for (char c = c1; c <= c2; ++c) {
                    char_class.insert(c);
                }
            } else {
                char_class.insert(c1);
            }
        }

        return {char_class, i + 1};
    }

    bool findIn(const string& input) const { return findIn(input, 0, 0); }

    bool findIn(const string& input, size_t i, size_t j) const
    {
        if (j == pattern.size()) // if we're at the end of pattern's characters
            return i == input.size(); // true if input is also finished else false

        if (pattern[j] == '[') {
            auto [char_class, next_j] = parseCharacterClass(j + 1);
            if (i < input.size() && char_class.count(input[i]) > 0)
                return findIn(input, i + 1, next_j);
        } else
        // still have input and
        // either the pattern is a dot that matches to everything or the character exactly matches
        // then divide the problem into a smaller problem because this part fits to the rules
        // solve the rest of the problem similarly
        if (i < input.size() && (pattern[j] == '.' || input[i] == pattern[j]))
            return findIn(input, i + 1, j + 1);

        return false;
    }
};

int main() {
    auto matcher = RegexMatcher("h.[a-zA-C]lo");
    cout << boolalpha << matcher.findIn("hello") << endl; // true
    cout << boolalpha << matcher.findIn("hAllo") << endl; // true
    cout << boolalpha << matcher.findIn("hillo") << endl; // true
    cout << boolalpha << matcher.findIn("heALo") << endl; // false
    return 0;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// In this takehome;
// You can only use the C++ stuff that we covered during our lectures.
// You will be penalized by -10 points per individual usage out of our lecture's content.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Valid content is ANYTHING that can be found in our lecture videos, lecture's GitHub Repo,
// or anything provided in this sample code.
// If you are not sure, you must ask us (both TA and instructor) in the same email
// and get a consent to use the asked core language or standard library feature in your solution.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Consent emails that don't include both the TA and the instructor WILL NOT BE ANSWERED.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// First day of the exam, no questions will be answered until it is 15:00.
// Email responses will be given at worst by 21:00 in the same day.
// You asked at 13:45, you are answered by 21:00 that day.
// You asked at 21:15, you are answered by 21:00 the next day.
// You cannot ask questions about the exam to anybody else.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// You can #include files only from the C/C++ standard libraries.
// You cannot use #include <regex> of course
// You will be uploading a SINGLE file as a solution to the LMS.
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Either by improving the template provided for you or writing everything from scratch;
// Write a regular expression matcher class that can do below:

// Q1) 10 points
// Write a struct that can hold the result of a match operation (i.e. RxResult?).
// The stored information will cover:
// - if a match has been found or not ("matched" attribute maybe?)
// - the regions of the input that aligns with the paranthesis in the search pattern

// Q2) 10 points
// Write a generic print function that only matches with RxResult struct(s) and
// prints its/tehir contents by using fold expressions
// exactly as indicated in the console output at the very bottom of this file.

// Q3) 15 points
// Current code exactly matches the pattern and input from its beginining to end fully.
// Any extra characters in the front of or at the end of the matched portion aren't allowed.
// Make the code flexible so that below code will match the "helLo" within "!_helLo_!"
// in spite of the additional character(s) around the searched pattern.
// RxMatcher("he[lL][lL]o").findIn("!_helLo_!");

// Q4) 25 points
// Current code only supports string containers. Improve the code so that it supports any container.
// Ensure that it works by enabling the commented out code in the main() function for
// containers storing INT and DOUBLE. You need to allow customization of your generic RegexMatcher class
// so that its pattern characters are customizable for different item typenames of a container.
// (look at the sample code in commented out main() function

// Q5) 20 points
// Add support for paranthesis characters that indicates certain regions of the pattern
// so that matcher returns a feedback on what a specific (...) region matched what.
// Adding support for paranthesis is only required for RegexMatch<string>.
// You need to support paranthesis within paranthesis as well
// Look at the commented out main() function and its console output provided for you
// so that you can understand how it will work

// Q6) 20 points
// Improve character class support in such a way that
//   auto matcher = RxMatcher(vector{1.0, CFG::DOT, CFG::CCbegin, 10.0, CFG::DASH, 20.0, CFG::CCend, 4.0});
//   matcher.findIn(vector{1.0, 2.0, 15.5, 4.0}).matched; // --> returns true
// lines return true. This means that character-class 10.0 DASH 20.0 also supports 15.5 as valid.

// this is the main() function that needs to work correctly after you completed the takehome fully

//int main() {
//    cout << boolalpha;
//    {
//        cout << "STRING matcher" << endl;
//        auto matcher = RxMatcher("h((.[a-z])(lo))");
//        print(
//            matcher.findIn("hello "),
//            matcher.findIn("hallo"),
//            matcher.findIn("_hEblo!"),
//            matcher.findIn("heako")
//            );
//    }
//    cout << endl;

//    {
//        cout << "INT matcher" << endl;
//        using CFG = RxConfig<int>;
//        auto matcher1 = RxMatcher(vector{1, CFG::DOT, CFG::CCbegin, 10, 20, CFG::CCend, 4});
//        cout << matcher1.findIn(vector{1, 2, 20, 4}).matched << endl;
//        cout << matcher1.findIn(vector{1, 2, 15, 4}).matched << endl;

//        auto matcher2 = RxMatcher(vector{1, CFG::DOT, CFG::CCbegin, 10, CFG::DASH, 20, CFG::CCend, 4});
//        cout << matcher2.findIn(vector{1, 2, 15, 4}).matched << endl;
//    }
//    cout << endl;

//    {
//        cout << "DOUBLE matcher" << endl;
//        using CFG = RxConfig<double>;
//        auto matcher1 = RxMatcher(vector{1.1, CFG::DOT, CFG::CCbegin, 10.0, CFG::DASH, 20.0, CFG::CCend, 4.0});
//        cout << matcher1.findIn(vector{1.1, 2.5, 15.5, 4.0}).matched << endl;
//    }
//    return 0;
//}


// Correct OUTPUT that will be exactly written to the console is below:

// STRING matcher
// Input: "hello "
// Matched: true  (1,5)=ello (1,3)=el (3,5)=lo
// Input: "hallo"
// Matched: true  (1,5)=allo (1,3)=al (3,5)=lo
// Input: "_hEblo!"
// Matched: true  (2,6)=Eblo (2,4)=Eb (4,6)=lo
// Input: "heako"
// Matched: false
//
// INT matcher
// true
// false
// true
//
// DOUBLE matcher
// true

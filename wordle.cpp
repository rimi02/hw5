
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helper (const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& answers, std::string curr, std::map<char, int> floating_map);


// Definition of primary wordle function
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> possible_words;

    // Generate all possible combinations of fixed and floating letters
    for (int i = 0; i < in.length(); i++) {
        // Skip if the current position is not a blank space
        if (in[i] != '-') continue;

        // Replace the blank space with all possible letters of the alphabet
        for (char c = 'a'; c <= 'z'; c++) {
            std::string word = in;
            word[i] = c;

            // Add floating characters to the word in any remaining blank spaces
            for (int j = 0; j < floating.length(); j++) {
                for (int k = 0; k < word.length(); k++) {
                    if (word[k] == '-') {
                        word[k] = floating[j];
                        break;
                    }
                }
            }

            // Check if the generated word is a valid English-language word
            if (dict.find(word) != dict.end()) {
                // Add the word to the set of possible words
                possible_words.insert(word);
            }
        }
    }

    return possible_words;
}


void helper (const std::string& in, const std::string& floating, const std::set<std::string>& dict, 
std::set<std::string>& answers, std::string curr, std::map<char, int> floating_map) {
    // base case
    if (curr.size() == in.size()) {
        if (dict.find(curr) != dict.end()) {
            for(auto s : answers){
                    cout << s << endl;
                }
            answers.insert(curr);
        }
        return;
    }
    // if the current character is not a dash, recurse to the next character
    if (in[curr.size()] != '-') {
        helper(in, floating, dict, answers, curr + in[curr.size()], floating_map);
        return;
    }
    // if the floating map is empty, we can only use letters from the dictionary
    if (floating_map.empty()) {
        for (char c = 'a'; c <= 'z'; c++) {
            // check if the word is valid before recursing
            if (dict.find(curr + c) != dict.end()) {
                helper(in, floating, dict, answers, curr + c, floating_map);
            }
        }
    }
    // if the floating map is not empty, we can use letters from the floating map
    else {
        for (auto it = floating_map.begin(); it != floating_map.end(); it++) {
            // if the floating map has a letter that is in the dictionary, we can use it
            if (dict.find(curr + it->first) != dict.end()) {
                helper(in, floating, dict, answers, curr + it->first, floating_map);
            }
            // if the floating map has a letter that is not in the dictionary, we can use it
            else {
                helper(in, floating, dict, answers, curr + it->first, floating_map);
            }
            // if the floating map has a letter that is in the dictionary, we can use it
            if (it->second > 1) {
                it->second -= 1;
                // check if the word is valid before recursing
                if (dict.find(curr + it->first) != dict.end()) {
                    helper(in, floating, dict, answers, curr + it->first, floating_map);
                }
                it->second += 1;
            }
        }
    }
}


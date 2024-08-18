#include "fdx.h"

//#include "../../../../../lib/fastText/src/fasttext.h"
#include <boost/algorithm/string.hpp>

#include <iostream>

namespace algos {

void FDX::GenerateEmbedding() {
    for(size_t attr_idx = 0; attr_idx < column_names_.size(); ++attr_idx) {
        std::unordered_set<std::string_view> unique_cells;
        std::unordered_set<std::string_view> unique_words;
        std::unordered_map<std::string_view, uint32_t> word_vocab;
        uint32_t next_word_id = 0;
        size_t max_len = 0;

        for(size_t tuple_idx = 0; tuple_idx < tuples_.size(); ++tuple_idx) {
            std::string_view cell = tuples_[tuple_idx][attr_idx];
            unique_cells.emplace(cell);

            std::vector<std::string> words;
            //boost::split(words, cell, boost::is_space(), boost::token_compress_on);

            std::remove_if(words.begin(), words.end(),
                                       [](std::string_view const& word) {
                return word.empty(); });

            max_len = std::max(max_len, words.size());
            std::for_each(
                    words.begin(), words.end(),
                    [&unique_words, &word_vocab, &next_word_id](std::string_view const& word) {
                        if (unique_words.find(word) == unique_words.end()) {
                            unique_words.emplace(word);
                            word_vocab[word] = next_word_id;
                            next_word_id++;
                        }
                    });
        }

        //fasttext::FastText ft_model;
        //ft_model.train({})
    }
}

}
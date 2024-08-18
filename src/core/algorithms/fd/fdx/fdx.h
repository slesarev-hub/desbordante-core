#pragma once

#include "algorithms/fd/fd_algorithm.h"
#include "config/tabular_data/input_table_type.h"

namespace algos {

class FDX : public FDAlgorithm {
public:
    FDX() : FDAlgorithm({"embedding"}) {
        //RegisterOptions();
        //MakeOptionsAvailable({config::kTableOpt.GetName()});
        GenerateEmbedding();
    }

    void GenerateEmbedding();

private:
    config::InputTable input_table_;
    size_t number_of_attributes_;
    std::vector<std::string> column_names_;
    std::vector<std::vector<std::string>> tuples_;

    void LoadDataInternal() final {
        number_of_attributes_ = input_table_->GetNumberOfColumns();
        if (number_of_attributes_ == 0) {
            throw std::runtime_error("Unable to work on an empty dataset.");
        }
        column_names_.resize(number_of_attributes_);

        for (size_t i = 0; i < number_of_attributes_; ++i) {
            column_names_[i] = input_table_->GetColumnName(static_cast<int>(i));
        }

        std::vector<std::string> next_line;
        while (input_table_->HasNextRow()) {
            next_line = input_table_->GetNextRow();
            if (next_line.empty()) break;
            tuples_.emplace_back(number_of_attributes_);
            for (size_t i = 0; i < number_of_attributes_; ++i) {
                tuples_.back()[i] = next_line[i];
            }
        }
    }

    unsigned long long ExecuteInternal() final {
        GenerateEmbedding();
        return 0;
    }

    void ResetStateFd() final {

    }
};

}  // namespace algos
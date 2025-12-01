#pragma once
#include <string>
#include <cstdint>
#include <sstream>

#include "RunMetaData.hpp"

struct RunResult {
    // identifiers
    std::string impl;         // "binheap", "binomial", "oracle", ...
    std::string trace_path;   // e.g., "traces/huffman_N_1024_seed_23.trace"
    std::string trace_type;   // full_operation, insert_only, extract_min_only
    std::string csvFile;
    RunMetaData run_meta_data;

    RunResult(const RunMetaData& meta_data): run_meta_data(meta_data) {}

    // timing
    std::int64_t elapsed_ns = 0;   // total replay time (nanoseconds)

    // operation counts
    long inserts     = 0;  // 'I'
    long erase = 0;  // 'E'

    // convenience
    long total_ops() const {
        return inserts + erase;
    }
    double elapsed_ms() const {
        return static_cast<double>(elapsed_ns) / 1e6;
    }
    double ops_per_sec() const {
        const double secs = static_cast<double>(elapsed_ns) / 1e9;
        return secs > 0.0 ? static_cast<double>(total_ops()) / secs : 0.0;
    }

    // CSV helpers
    static std::string csv_header() {
    return std::string("impl") +
           std::string(",profile") +
           std::string(",trace_path") +
           std::string(",N") +
           std::string(",seed") +
           std::string(",elapsed_ms") +
           std::string(",ops_total") + 
	   std::string(",inserts") + 
	   std::string(",erases,");
    }


    std::string to_short_csv_row() const {
        std::ostringstream os;
        os << impl << ','
          << run_meta_data.seed << ','
          << run_meta_data.N << ','
          << elapsed_ms() << ','
	  << inserts + erase << ','
	  << inserts << ','
	  << erase;

        return os.str();
    }

    std::string to_csv_row() const {
        std::ostringstream os;
        os << impl << ','
           << run_meta_data.profile << ','
           << trace_path << ','
           << run_meta_data.N << ','
           << run_meta_data.seed << ','
           << elapsed_ms() << ','
           << total_ops() << ','
           << inserts << ','
	   << erase << ',';
        return os.str();
    }
};

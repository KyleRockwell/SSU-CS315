#pragma once
#include <string>
#include <cstdint>
#include <sstream>

#include "RunMetaData.hpp"

struct RunResult {
    // identifiers
    enum PROBE_TYPE {SINGLE, DOUBLE};

    PROBE_TYPE probeType;
    bool 	 shouldCompact		;
    
    std::int64_t TABLE_SIZE		;
    std::string impl			;         // "binheap", "binomial", "oracle", ...
    std::string trace_path		;   // e.g., "traces/huffman_N_1024_seed_23.trace"
    std::string trace_type		;   // full_operation, insert_only, extract_min_only
    std::string csvFile			;
    std::int64_t numLookups		;	
    std::int64_t numDeletes		;
    std::int64_t numInserts		;
    int		 numCompactions		;
    std::int64_t numHits 		;
    std::int64_t numMisses 		;
    std::int64_t numFullScans 		;
    std::int64_t totalProbes 		;
    std::int64_t numberOfActive 	;	
    std::int64_t numberOfTombstones 	;
    std::int64_t maxTombstones 		;
    std::int64_t maxValuesInTable 	;

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
    return std::string("impl"			) +
           std::string(",profile"		) +
           std::string(",trace_path"		) +
           std::string(",N"			) +
           std::string(",seed"			) +
           std::string(",elapsed_ms"		) +
           std::string(",ops_total"		) + 
	   std::string(",inserts"		) + 
	   std::string(",erases,"		) +
    	   std::string("table_size"		) +
           std::string(",active"		) +
           std::string(",available"		) +
           std::string(",tombstones"		) +
           std::string(",total_probes"		) +
           std::string(",inserts"		) + 
	   std::string(",deletes"		) + 
	   std::string(",lookups"		) +
           std::string(",full_scans"		) + 
	   std::string(",compactions"		) +
	   std::string(",max_in_table"		) +
           std::string(",available_pct"		) + 
	   std::string(",load_factor_pct"	) +
           std::string(",eff_load_factor_pct" 	) +
           std::string(",tombstones_pct"      	) + 
	   std::string(",average_probes"      	) +
           std::string(",probe_type"		) + 
	   std::string(",compaction_state"	);
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
        os 
	<< impl 						<< ','
	<< run_meta_data.profile			 	<< ','
	<< trace_path 						<< ','
	<< run_meta_data.N 					<< ','
	<< run_meta_data.seed 					<< ','
	<< elapsed_ms() 					<< ','
	<< total_ops() 						<< ','
	<< inserts 						<< ','
	<< erase 						<< ',';

        return os.str()+
   	std::to_string(TABLE_SIZE) + "," + // table size
        std::to_string(numberOfActive) + "," + // active
        std::to_string(TABLE_SIZE - numberOfTombstones - numberOfActive) + "," + // available
        std::to_string(numberOfTombstones) + "," + // tombstones
        std::to_string(totalProbes) + "," + // totalProbes
        std::to_string(numInserts) + "," + // inserts
        std::to_string(numDeletes) + "," + // deletes
        std::to_string(numLookups) + "," + // lookups
        std::to_string(numFullScans) + "," + // full scans
        std::to_string(numCompactions) + "," + // compactions
        std::to_string(maxValuesInTable) + "," + // max_in_table
        std::to_string(
            static_cast<int>(static_cast<double>(TABLE_SIZE - numberOfTombstones - numberOfActive) /
                static_cast<double>(TABLE_SIZE) * 100)) + "," + // ratio available
        std::to_string(static_cast<int>(static_cast<double>(numberOfActive) / static_cast<double>(TABLE_SIZE) * 100))
        + "," + // load factor
        std::to_string(
            static_cast<int>(static_cast<double>(numberOfActive + numberOfTombstones) / static_cast<double>(
                                 TABLE_SIZE) * 100)) + "," + // effective load factor
        std::to_string(
            static_cast<int>(static_cast<double>(numberOfTombstones) / static_cast<double>(TABLE_SIZE) * 100)) + ","
        + // ratio tombstones
        std::to_string(static_cast<double>(totalProbes) / static_cast<double>(numInserts + numDeletes + numLookups)) +
        ((probeType == SINGLE) ? ",single," : ",double,") +
        (shouldCompact ? "compaction_on" : "compaction_off");
    }
};

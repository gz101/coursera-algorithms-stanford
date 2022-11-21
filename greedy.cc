#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>


size_t greedy(std::vector<std::pair<int, int>>& jobs, int correct);

// You should NOT assume that edge weights or lengths are distinct.
// Your task in this problem is to run the greedy algorithm that schedules jobs 
//   in decreasing order of the difference (weight - length).
// Recall from lecture that this algorithm is not always optimal.
//   IMPORTANT: if two jobs have equal difference (weight - length), you should 
//   schedule the job with higher weight first.  
// Beware: if you break ties in a different way, you are likely to get the wrong
//   answer. You should report the sum of weighted completion times of the 
//   resulting schedule --- a positive integer --- in the box below. 
// ADVICE: If you get the wrong answer, try out some small test cases to debug
//   your algorithm (and post your test cases to the discussion forum).
void greedy_wrong(std::vector<std::pair<int, int>>& jobs);

// Your task now is to run the greedy algorithm that schedules jobs (optimally)
//   in decreasing order of the ratio (weight/length).
// In this algorithm, it does not matter how you break ties. You should report 
//   the sum of weighted completion times of the resulting schedule --- a 
//   positive integer --- in the box below. 
void greedy_correct(std::vector<std::pair<int, int>>& jobs);


int main(int argc, char** argv) {
    // Only accepts 1 argument - `1`(correct) or `0` (wrong).
    if (argc != 2) {
        std::cout << "USAGE: requires exactly 1 argument." << std::endl;
        return EXIT_FAILURE;
    }

    int correct_flag = atoi(argv[1]);
    if (correct_flag < 0 || correct_flag > 1) {
        std::cout << "USAGE: either `0` or `1` is needed." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Starting greedy algorithm..." << std::endl;

    // Open input file.
    std::ifstream input_file("./input/jobs.txt");
    if (!input_file.is_open()) {
        std::cout << "ERROR: error reading input file." << std::endl;
        return EXIT_FAILURE;
    }

    // Number of lines of input.
    size_t N;
    input_file >> N;

    // Store each weight, length in a vector of pairs.
    std::vector<std::pair<int, int>> jobs;

    // Read from the input file, line by line.
    int weight;
    int length;
    while (input_file >> weight >> length) {
        jobs.push_back(std::make_pair(weight, length));
    }

    std::cout << "Read " << jobs.size() << " lines in total." << std::endl;

    // Run algorithm.
    std::cout << "Weighted sum: " << greedy(jobs, correct_flag) << std::endl;

    // Finish and tidy up.
    input_file.close();
    std::cout << "Algorithm terminated successfully." << std::endl;
    return EXIT_SUCCESS;
}


size_t greedy(std::vector<std::pair<int, int>>& jobs, int correct_flag) {
    // Switch between `greedy_correct()` (1) and `greedy_wrong()` (0).
    if (correct_flag) {
        greedy_correct(jobs);
    } else {
        greedy_wrong(jobs);
    }

    size_t weighted_sum = 0.0;
    size_t time = 0;

    for (auto it = jobs.begin(); it != jobs.end(); ++it) {
        time += it->second;
        weighted_sum += it->first * time;
    }

    return weighted_sum;
}


// Solution: 69119377652
void greedy_wrong(std::vector<std::pair<int, int>>& jobs) {
    // Sort in descending order by:
    //   (1) weight - length
    //   (2) weight
    std::sort(jobs.begin(), jobs.end(), [](const auto& lhs, const auto& rhs) {
        int diff_lhs = lhs.first - lhs.second;
        int diff_rhs = rhs.first - rhs.second;
        if (diff_lhs == diff_rhs) {
            return lhs.first > rhs.first;
        } else {
            return diff_lhs > diff_rhs;
        } 
    });
}


// Solution: 67311454237
void greedy_correct(std::vector<std::pair<int, int>>& jobs) {
    // Sort in descending order by:
    //   (1) weight / length
    std::sort(jobs.begin(), jobs.end(), [](const auto& lhs, const auto& rhs) {
        return ((double) lhs.first / lhs.second) > ((double) rhs.first / rhs.second); 
    });
}


// void Interpolation::calculate_responsibilities_lamdas(NgramLanguageModel& probabl , const std::vector<std::string>& query){
//     if (query.empty()) {
//         return;
//     }

//     for ( std::size_t i = 0; i < query.size(); i++ ){
//         if ( i == 0){
//         responsibility_unigram += 1.0;
//         }
//         else if( i == 1){
//         responsibility_unigram += (lamda_for_unigram * probabl.probability_of_unigram(query[i])) / (lamda_for_unigram * probabl.probability_of_unigram(query[i]) 
//         + lamda_for_bigram * probabl.probability_of_bigram(query[i-1] ,query[i]));  
//         responsibility_bigram += (lamda_for_bigram * probabl.probability_of_bigram(query[i-1] , query[i])) / (lamda_for_unigram * probabl.probability_of_unigram(query[i]) 
//         + lamda_for_bigram * probabl.probability_of_bigram(query[i-1] ,query[i]));
//         } else{
//         responsibility_unigram += (lamda_for_unigram * probabl.probability_of_unigram(query[i]) )/ ( lamda_for_unigram * probabl.probability_of_unigram(query[i]) 
//         + lamda_for_bigram * probabl.probability_of_bigram(query[i-1] ,query[i])  + lamda_for_trigram * 
//         probabl.probability_of_trigram(query[i-2] ,query[i-1], query[i]));

//         responsibility_bigram += (lamda_for_bigram * probabl.probability_of_bigram(query[i-1] ,query[i]) )/ ( lamda_for_unigram * probabl.probability_of_unigram(query[i]) 
//         + lamda_for_bigram * probabl.probability_of_bigram(query[i-1] ,query[i])  + lamda_for_trigram * 
//         probabl.probability_of_trigram(query[i-2] ,query[i-1], query[i]));

//         responsibility_trigram += (lamda_for_trigram * probabl.probability_of_trigram(query[i-2] ,query[i-1], query[i]))/ ( lamda_for_unigram * probabl.probability_of_unigram(query[i]) 
//         + lamda_for_bigram * probabl.probability_of_bigram(query[i-1] ,query[i])  + lamda_for_trigram * 
//         probabl.probability_of_trigram(query[i-2] ,query[i-1], query[i]));
//         }

//     }
//     lamda_for_unigram = responsibility_unigram / query.size();
//     lamda_for_bigram = responsibility_bigram / query.size();
//     lamda_for_trigram = responsibility_trigram / query.size();

//     responsibility_unigram = 0.0;
//     responsibility_bigram = 0.0;
//     responsibility_trigram = 0.0;
// }


#include <tokens.hpp>
#include <ngram_language_model.hpp>
#include <unordered_map>
#include <cstddef>
#include <interpolated_language.hpp>

void Interpolation::calculate_responsibilities_lamdas(NgramLanguageModel& probabl, const std::vector<std::string>& query) {
    if (query.empty()) {
        return;
    }
    std::size_t valid_positions = 0;
    for (std::size_t i = 0; i < query.size(); i++) {
        if (i == 0) {
            responsibility_unigram += 1.0;
        }
        else if (i == 1) {
            double unigram_probability = probabl.probability_of_unigram(query[i]);
            double bigram_probability = probabl.probability_of_bigram(query[i-1], query[i]);

            double unigram_contribution = lamda_for_unigram * unigram_probability;
            double bigram_contribution = lamda_for_bigram * bigram_probability;

            double denominator = unigram_contribution + bigram_contribution;

            if (denominator > 0.0) {
                responsibility_unigram += unigram_contribution / denominator;
                responsibility_bigram += bigram_contribution / denominator;
                valid_positions++;
            }
        }
        else {
            double unigram_probability = probabl.probability_of_unigram(query[i]);
            double bigram_probability = probabl.probability_of_bigram(query[i-1], query[i]);
            double trigram_probability = probabl.probability_of_trigram(query[i-2], query[i-1], query[i]);

            double unigram_contribution = lamda_for_unigram * unigram_probability;
            double bigram_contribution = lamda_for_bigram * bigram_probability;
            double trigram_contribution = lamda_for_trigram * trigram_probability;

            double denominator = unigram_contribution + bigram_contribution + trigram_contribution;

            if (denominator > 0.0) {
                responsibility_unigram += unigram_contribution / denominator;
                responsibility_bigram += bigram_contribution / denominator;
                responsibility_trigram += trigram_contribution / denominator;
                valid_positions++;
            }
        }
    }

if (valid_positions > 0) {
    lamda_for_unigram = responsibility_unigram / valid_positions;
    lamda_for_bigram = responsibility_bigram / valid_positions;
    lamda_for_trigram = responsibility_trigram / valid_positions;
}

    responsibility_unigram = 0.0;
    responsibility_bigram = 0.0;
    responsibility_trigram = 0.0;
}

void Interpolation::train_calculation(NgramLanguageModel& probabl , const std::vector<std::string>& query){
    double e_uni = 1.0;
    double e_bi = 1.67;
    double e_tri = 1.52;
    old_lamda_for_unigram = lamda_for_unigram;
    old_lamda_for_bigram = lamda_for_bigram;
    old_lamda_for_trigram = lamda_for_trigram;
    double epsilon = 0.001;
    calculate_responsibilities_lamdas(probabl ,query);
    std::size_t counts = 0;
    std::size_t max_counts = 1000;
    while ((e_uni > epsilon || e_bi > epsilon ||  e_tri > epsilon) && counts < max_counts){
        calculate_responsibilities_lamdas(probabl ,query);
        e_uni = std::abs(old_lamda_for_unigram-lamda_for_unigram);
        e_bi = std::abs(old_lamda_for_bigram-lamda_for_bigram);
        e_tri = std::abs(old_lamda_for_trigram-lamda_for_trigram);
        old_lamda_for_unigram = lamda_for_unigram;
        old_lamda_for_bigram = lamda_for_bigram;
        old_lamda_for_trigram = lamda_for_trigram;
        counts++;
    }
}

double Interpolation::interpolate(double unigram, double bigram, double trigram) {
    return lamda_for_unigram * unigram
         + lamda_for_bigram * bigram
         + lamda_for_trigram * trigram;
}
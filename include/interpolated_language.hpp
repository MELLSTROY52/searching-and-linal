#pragma once 
#include <tokens.hpp>
#include <ngram_language_model.hpp>
#include<unordered_map>
#include <cstddef>
class Interpolation {
    private:
    double lamda_for_unigram =1.0/3.0 ;
    double lamda_for_bigram = 1.0/3.0;
    double lamda_for_trigram = 1.0/3.0;

    double responsibility_unigram = 0.0;
    double responsibility_bigram = 0.0;
    double responsibility_trigram = 0.0;

    double sum_unigram = 0.0;
    double sum_bigram = 0.0;
    double sum_trigram = 0.0;

    double old_lamda_for_unigram;
    double old_lamda_for_bigram;
    double old_lamda_for_trigram;

    public:
    void calculate_responsibilities_lamdas(NgramLanguageModel& probabl , const std::vector<std::string>& query);
    void train_calculation (NgramLanguageModel& probabl , const std::vector<std::string>& query);
    double interpolate(double unigram, double bigram, double trigram);

    double get_lambda_unigram() const {return lamda_for_unigram;}
    
    double get_lambda_bigram() const {return lamda_for_bigram;}
    
    double get_lambda_trigram() const {return lamda_for_trigram;}

    
};
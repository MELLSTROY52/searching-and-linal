#include <advanced_spellchecker.hpp>
#include <algorithm>


// std::size_t Levenshtein_func(std::string &query , std::string &word){
//     std::size_t n = query.size() +1;
//     std::size_t m = word.size() + 1;
//     std::vector<std::vector<std::size_t>>  matrix( n , std::vector<std::size_t>(  m, 0));

//     for ( std::size_t i = 0; i  < n; i++){
//         for ( std::size_t j = 0; j < m; j++){
//             if ( i == 0 || j ==0 ){
//                 matrix[i][j] = std::max( i , j);
//             }else{
//                 if ( query[i -1] == word[j -1]){
//                     matrix[i][j] = matrix[i-1][j-1];
//                 }else{
//                     matrix[i][j] = std::min({matrix[i-1][j-1] +1, matrix[i][j-1] +1, matrix[i-1][j]+1});
//             }
//         }
//     }
// }
// return matrix[n-1][m-1];
// }




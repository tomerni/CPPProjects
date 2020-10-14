//
// Created by tomer on 6/21/2020.
//

#ifndef EX5_RECOMMENDERSYSTEM_H
#define EX5_RECOMMENDERSYSTEM_H

#include <string>
#include <unordered_map>
#include <vector>
using std::unordered_map;
using std::string;
using std::vector;

/**
 * The RecommenderSystem Class
 */
class RecommenderSystem
{
public:
	/**
	 * Loads the data in the files to the private variables in the class
	 * @param moviesAttributesFilePath the path of the attributes file
	 * @param userRanksFilePath the path of the ranking file
	 * @return 0 on success, -1 on failure
	 */
	int loadData(const string& moviesAttributesFilePath, const string& userRanksFilePath);
	/**
	 * Recommends according the content method
	 * @param userName the user name
	 * @return the name of movie
	 */
	string recommendByContent(const string& userName) const;
	/**
	 * Predicts the score of the movie according the user
	 * @param movieName the movie name
	 * @param userName the user name
	 * @param k the number of movies to compare
	 * @return the ranking of the movie
	 */
	double predictMovieScoreForUser(const string& movieName, const string& userName, int k)
	const;
	/**
	 * Recommend the movie according to the CF method
	 * @param userName the name of the user
	 * @param k the number of movies to compare
	 * @return the name of the movie
	 */
	string recommendByCF(const string& userName, int k) const;
private:
	unordered_map<string, vector<double>> _attributes;
	unordered_map<string, vector<double>> _ranks;
	vector<string> _moviesOrder;
	vector<double> _moviesNorms;
	/**
	 * Parses the rank data
	 * @param rank the rank file
	 * @return unordered map with the name of the user and his rankings
	 */
	static unordered_map<string, vector<double>> _readRank(std::ifstream& rank);
	/**
	 * Parses the attributes file
	 * @param att the attributes file
	 * @return unordered map with the name of the movies as keys and the attributes vector as value
	 */
	static unordered_map<string, vector<double>> _readAtt(std::ifstream& att);
	/**
	 * Parses the first line of the ranking file
	 * @param rank the ranking file
	 * @return vector with the name of the movies according their order in the file
	 */
	static vector<string> _firstLineRank(std::ifstream& rank);
	/**
	 * creates a vector with the norms of the movies in the order of their appearance
	 * @param _attributes the map with the attributes of the movies
	 * @param order vector with the name of the movies
	 * @return vector with the norms of the movies in the order of their appearance
	 */
	static vector<double> _moviesNormCalc(const unordered_map<string, vector<double>>& _attributes,
										  const vector<string>& order);
	/**
	 * Creates the preference vector of the user
	 * @param vec
	 * @param order
	 * @param att
	 * @return
	 */
	static vector<double> _userPrefVector(const vector<double>& vec, const vector<string>& order,
										  const unordered_map<string, vector<double>>& att);
	/**
	 * Finds the movie with the best similarity to the movies that the user watched
	 * @param userVector
	 * @param norms
	 * @param norm
	 * @param att
	 * @param userPref
	 * @param movies
	 * @return
	 */
	static string _findBestSimilarity(const vector<double>& userVector, const vector<double>& norms,
			                          double norm, const unordered_map<string, vector<double>>& att,
			                          vector<double>& userPref, const vector<string>& movies);
};

#endif //EX5_RECOMMENDERSYSTEM_H

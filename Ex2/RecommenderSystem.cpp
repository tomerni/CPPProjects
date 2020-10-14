//
// Created by tomer on 6/21/2020.
//

#include "RecommenderSystem.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

#define FAIL -1
#define SUCCESS 0
#define PATHERR "Unable to open file "
#define USERERR "USER NOT FOUND"

using std::string;
using std::vector;
using std::istringstream;

/**
 * Calculates the norm of the vector
 * @param vec vector of doubles
 * @return the value of the norm
 */
static double normCalc(const vector<double>& vec)
{
	double sum = 0;
	for(const double & it : vec)
	{
		sum += it*it;
	}
	return sqrt(sum);
}

/**
 * Parses the rank data
 * @param rank the rank file
 * @return unordered map with the name of the user and his rankings
 */
unordered_map<string, vector<double>> RecommenderSystem::_readRank(std::ifstream& rank)
{
	string line;
	unordered_map< string, vector<double>> rankMap;
	while(std::getline(rank, line))
	{
		vector<double> rankVector;
		istringstream movieLine(line);
		string userName;
		string chunk;
		movieLine >> userName;
		while(movieLine >> chunk)
		{
			if(chunk == "NA")
			{
				rankVector.push_back(0);
			}
			else
			{
				rankVector.push_back(std::stod(chunk));
			}
		}
		rankMap[userName] = rankVector;
	}
	return rankMap;
}

/**
 * Parses the attributes file
 * @param att the attributes file
 * @return unordered map with the name of the movies as keys and the attributes vector as value
 */
unordered_map<string, vector<double>> RecommenderSystem::_readAtt(std::ifstream& att)
{
	string line;
	unordered_map<string, vector<double>> attMap;
	std::getline(att, line);
	while(!att.eof())
	{
		vector<double> rankVector;
		istringstream movieLine(line);
		string movieName;
		string rank;
		movieLine >> movieName;
		while(movieLine >> rank)
		{
			rankVector.push_back(std::stod(rank));
		}
		attMap[movieName] = rankVector;
		std::getline(att, line);
	}
	return attMap;
}

/**
 * Parses the first line of the ranking file
 * @param rank the ranking file
 * @return vector with the name of the movies according their order in the file
 */
vector<string> RecommenderSystem::_firstLineRank(std::ifstream& rank)
{
	vector<string> order;
	string movieOrder;
	std::getline(rank, movieOrder);
	istringstream movieLine(movieOrder);
	string movieName;
	while(movieLine >> movieName)
	{
		order.push_back(movieName);
	}
	return order;
}

/**
 * creates a vector with the norms of the movies in the order of their appearance
 * @param _attributes the map with the attributes of the movies
 * @param order vector with the name of the movies
 * @return vector with the norms of the movies in the order of their appearance
 */
vector<double> RecommenderSystem::_moviesNormCalc(const unordered_map<string, vector<double>>&
                                                  _attributes, const vector<string>& order)
{
	vector<double> temp;
	temp.reserve(order.size());
	for(const string& it : order)
	{
		temp.push_back(normCalc(_attributes.at(it)));
	}
	return temp;
}

/**
 * Loads the data in the files to the private variables in the class
 * @param moviesAttributesFilePath the path of the attributes file
 * @param userRanksFilePath the path of the ranking file
 * @return 0 on success, -1 on failure
 */
int RecommenderSystem::loadData(const string& moviesAttributesFilePath, const string&
                                userRanksFilePath)
{
	std::ifstream att, rank;
	att.open(moviesAttributesFilePath);
	rank.open(userRanksFilePath);
	if(!att.is_open())
	{
		std::cerr << PATHERR << moviesAttributesFilePath;
		return FAIL;
	}
	if(!rank.is_open())
	{
		std::cerr << PATHERR << userRanksFilePath;
		att.close();
		return FAIL;
	}
	if(!rank.good() || !att.good())
	{
		return FAIL;
	}
	_attributes = _readAtt(att);
	_moviesOrder = _firstLineRank(rank);
	_moviesNorms = _moviesNormCalc(_attributes, _moviesOrder);
	_ranks = _readRank(rank);
	att.close();
	rank.close();
	return SUCCESS;
}

/**
 * Creates the normalized vector of the user
 * @param userVector the vector of the user ranking
 * @return normalized vector of the user
 */
static vector<double> normalizeVector(const vector<double>& userVector)
{
	vector<double> temp;
	double sum = 0;
	int counter = 0;
	for(const double & it : userVector)
	{
		if(it != 0)
		{
			sum += it;
			counter++;
		}
	}
	double avg = sum / counter;
	for(const double & it : userVector)
	{
		if(it != 0)
		{
			temp.push_back(it - avg);
		}
		else
		{
			temp.push_back(0);
		}
	}
	return temp;
}

/**
 * Creates the preference vector of the user
 * @param vec
 * @param order
 * @param att
 * @return
 */
vector<double> RecommenderSystem::_userPrefVector(const vector<double>& vec, const vector<string>&
                                                  order, const unordered_map<string,
                                                  vector<double>>&
                                                  att)
{
	vector<double> temp(att.at(order[0]).size());
	for(int i = 0; i < (int) vec.size(); ++i)
	{
		if(vec[i] != 0)
		{
			const vector<double>& res = att.at(order[i]);
			for(int j = 0; j < (int) res.size(); ++j)
			{
				double what = vec[i] * res[j];
				temp[j] += what;
			}
		}
	}
	return temp;
}

/**
 * Calculates the scalar multiplication of the vectors
 * @param pref
 * @param movie
 * @return
 */
static double calcScalarMulti(const vector<double>& pref, const vector<double>& movie)
{
	double sum = 0;
	for(int i = 0; i < (int) pref.size(); ++i)
	{
		sum += pref[i] * movie[i];
	}
	return sum;
}

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
string RecommenderSystem::_findBestSimilarity(const vector<double>& userVector, const
                                              vector<double>& norms, double norm, const
                                              unordered_map<
                                              string, vector<double>>& att, vector<double>&
                                              userPref, const vector<string>& movies)
{
	string res;
	double max = -1;
	for(int i = 0; i < (int) userVector.size(); i++)
	{
		if(userVector[i] == 0)
		{
			double mone = calcScalarMulti(userPref, att.at(movies[i]));
			double mehene = norm * norms[i];
			if(mone / mehene > max)
			{
				max = mone / mehene;
				res = movies[i];
			}
		}
	}
	return res;
}

/**
 * Recommends according the content method
 * @param userName the user name
 * @return the name of movie
 */
string RecommenderSystem::recommendByContent(const string &userName) const
{
	if(_ranks.find(userName) == _ranks.end())
	{
		return USERERR;
	}
	vector<double> userVector = _ranks.at(userName);
	vector<double> userVectorNormalized = normalizeVector(userVector);
	vector<double> userPref = _userPrefVector(userVectorNormalized, _moviesOrder, _attributes);
	double userPrefNorm = normCalc(userPref);
	return _findBestSimilarity(userVector, _moviesNorms, userPrefNorm, _attributes, userPref,
			_moviesOrder);
}

/**
 * Predicts the score of the movie according the user
 * @param movieName the movie name
 * @param userName the user name
 * @param k the number of movies to compare
 * @return the ranking of the movie
 */
double RecommenderSystem::predictMovieScoreForUser(const string &movieName, const string &userName,
		                                           const int k) const
{
	if(_attributes.find(movieName) == _attributes.end() || _ranks.find(userName) == _ranks.end())
	{
		return FAIL;
	}
	vector<double> userMovies = _ranks.at(userName);
	vector<double> movieRank = _attributes.at(movieName);
	double norm = normCalc(movieRank);
	vector< std::pair<double, double> > res;
	for(int i = 0; i < (int) userMovies.size(); ++i)
	{
		if(userMovies[i] != 0)
		{
			double mone = calcScalarMulti(movieRank, _attributes.at(_moviesOrder[i]));
			double mehene = _moviesNorms[i] * norm;
			res.emplace_back((mone / m

			ehene), userMovies[i]);
		}
	}
	std::sort(res.begin(), res.end());
	double mone = 0, mehene = 0;
	for(int j = (int) res.size() - k; j < (int) res.size(); ++j)
	{
		mone += res[j].first * res[j].second;
		mehene += res[j].first;
	}
	return mone / mehene;
}

/**
 * Recommend the movie according to the CF method
 * @param userName the name of the user
 * @param k the number of movies to compare
 * @return the name of the movie
 */
string RecommenderSystem::recommendByCF(const string& userName, const int k) const
{
	if(_ranks.find(userName) == _ranks.end())
	{
		return USERERR;
	}
	string result;
	double maxRank = 0;
	vector<double> userMovies = _ranks.at(userName);
	for(int i = 0; i < (int) userMovies.size(); ++i)
	{
		if(userMovies[i] == 0)
		{
			double predictionRank = predictMovieScoreForUser(_moviesOrder[i], userName, k);
			if(predictionRank > maxRank)
			{
				maxRank = predictionRank;
				result = _moviesOrder[i];
			}
		}
	}
	return result;
}
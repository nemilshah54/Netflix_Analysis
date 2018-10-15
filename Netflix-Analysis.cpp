/*main.cpp*/

//
// Netflix Analysis program in modern C++.
//
// << Nemil R Shah >>
// U. of Illinois, Chicago
// CS 341: Fall 2018
// Project 02
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include  <chrono>

using namespace std;

class Movie
{
private:
	//MovieID, MovieName, PubYear
	long int movieID;
	string movieName;
	int pubYear;

	// Additional data fields to keep track of ratings and reviews.
	int numReviews, numOnestar, numTwostar, numThreestar, numFourstar, numFivestar;

public:

	Movie( long int movieIDD, std::string movieNamee, int pubYearr, int one, int two, int three, int four, int five, int numR)
		: movieID(movieIDD), movieName(movieNamee), pubYear(pubYearr), numOnestar(one), numTwostar(two), numThreestar(three), numFourstar(four), numFivestar(five), numReviews(numR) 
	{ }

	// Copy custructor.
	Movie(const Movie& other)
		: movieID(other.movieID), movieName(other.movieName), pubYear(other.pubYear), numOnestar(other.numOnestar), numTwostar(other.numTwostar), numThreestar(other.numThreestar), numFourstar(other.numFourstar), numFivestar(other.numFivestar), numReviews(other.numReviews)
	{}

	//getters functions of private data fields.
	int getmovieID()
	{
		return movieID;
	}

	string getmovieName()
	{
		return movieName;
	}

	int getpubYear()
	{
		return pubYear;
	}

	int getNumReviews()
	{
		return numReviews;
	}

	float getAverage()
	{
		int sum, total;
		float average;
		sum = total = 0;

		if (numReviews == 0)
			return  0;  

		sum = (numOnestar * 1) + (numTwostar * 2) + (numThreestar * 3) + (numFourstar * 4) + (numFivestar * 5);
		total = numReviews;
		average = (float)sum / total;
		return average;
	}
	
	//Below functions updates the neccessary private fields of this class like total reviews and each stars.
	void addOne()
	{
		numOnestar++;
	}

	void addTwo()
	{
		numTwostar++;
	}

	void addThree()
	{
		numThreestar++;
	}

	void addFour()
	{
		numFourstar++;
	}

	void addFive()
	{
		numFivestar++;
	}

	void addReview()
	{
		numReviews++;
	}

	// PRINTS THE MOVIE CLASS INFORMATION.
	void print()
	{
		cout << "Movie:\t" << "'" << movieName << "'" << endl;
		cout << "Year:\t" << pubYear << endl;
		if (numReviews != 0	)
			cout << "Avg rating:\t" << getAverage() << endl;
		if (numReviews == 0)
			cout << "Avg rating:\t" << numReviews  <<endl;

		cout << "Num reviews:\t" << numReviews << endl;
		cout << "1 star: \t" << numOnestar << endl;
		cout << "2 stars:\t" << numTwostar << endl;
		cout << "3 stars:\t" << numThreestar << endl;
		cout << "4 stars:\t" << numFourstar << endl;
		cout << "5 stars:\t" << numFivestar << endl;
	}

};

class Review
{
private:
	//ReviewID, MovieID, UserID, Rating, ReviewDate
	long int  reviewID, userID, movieID;
	int rate;
	string reviewDate;

public:
	// Parametized constructor.
	Review(long int reviewIDD, long int movieIDD, long int userIDD, int ratee, std::string reviewDatee)
		: reviewID(reviewIDD), movieID(movieIDD), userID (userIDD),  rate(ratee), reviewDate(reviewDatee)
	{ }

	// Copy constructor.
	Review(const Review& other)
		: reviewID(other.reviewID), movieID(other.movieID), userID(other.userID), rate(other.rate), reviewDate(other.reviewDate)
	{}

	// Move constructor.
	Review(Review&& other)
		: reviewID(std::move(other.reviewID)), movieID(std::move(other.movieID)), userID(std::move(other.userID)), rate(std::move(other.rate)), reviewDate(std::move(other.reviewDate))
	{}

	// Getter functions.
	int getMovieID()
	{
		return movieID;
	}

	long int getUserId()
	{
		return userID;
	}

	int getRate()
	{
		return rate;
	}

	string getDate()
	{
		return reviewDate;
	}

	// PRINTS THE REVIEW CLASS INFORMATION.
	void print(map <int, Movie> M)
	{
		cout << "Movie: " << getMovieID() << " (" << M.find(getMovieID())->second.getmovieName() << ")" << endl;
		cout << "Num starts: " << getRate() << endl;
		cout << "User id: " << getUserId() << endl;
		cout << "Date: " << getDate() << endl;
	}
};


// READ INPUT MOVIE DATA AND RETURN MAP CONTAINER.
map <int, Movie> InputMovies(string filename)
{
	
	map < int, Movie> M;          // MAP CONTAINER. CONTAINS THE PAIRS. Key--->movieid. Object--->Movie.

	// Variables to get the data from files.
	string movieName, value, line;
	long int movieid;
	int pubyear;
	int one, two, three, four, five, numR;
	one = two = three = four = five = numR = 0;

	// File format: movieid, movieName, pubyear

	ifstream file(filename);

	getline(file, line);   // skip first line of file.

	cout << "Reading movies... ";
	int i = 0;       // Counts the number of movies
	while (getline(file, line))
	{
		//cout << " enter111111" << endl;
		stringstream  ss(line);

		getline(ss, value, ',');
		movieid = stol(value);

		getline(ss, movieName, ',');

		getline(ss, value, ',');
		pubyear = stoi(value);

		M.emplace(movieid, Movie(movieid, movieName, pubyear, one, two, three, four, five, numR));
		i++;
	}
	cout << i << endl;
	return M;
}


// READ INPUT REVIEW DATA AND RETURN MAP CONTAINER.
map <int, Review> InputReviews(string filename, map < int, Movie> &M)
{

	map < int, Review> R;          // REVIEW CONTAINER. CONTAINS THE PAIRS. Key--->reviewid. Object--->Review
  
	//// Variables to get the data from files.
	string reviewDate, value, line;
	long int reviewid, userid, movieid;
    int rate;

	// File format: ReviewID,MovieID,UserID,Rating,ReviewDate

	ifstream file(filename);

	getline(file, line);   // skip first line of file.

	cout << "Reading reviews...";
	long int k = 0;         // Count the number of reviews.
	while (getline(file, line))
	{
		k++;
		stringstream  ss(line);

		getline(ss, value, ',');
		reviewid = stol(value);

		getline(ss, value, ',');
		movieid = stol(value);

		getline(ss, value, ',');
		userid = stol(value);


		getline(ss, value, ',');
		rate = stoi(value);

		getline(ss, reviewDate, ',');

		R.emplace(reviewid, Review(reviewid, movieid, userid, rate, reviewDate));

		M.at(movieid).addReview();      // Update the number of review in movie class.

		switch (rate)
		{
		case 1:
			M.at(movieid).addOne();     // Update the number of 1 stars in movie class.
			break;

		case 2:
			M.at(movieid).addTwo();      // Update the number of 2 stars in movie class.
			break;
		case 3:
			M.at(movieid).addThree();     // Update the number of 3 stars in movie class.
			break;
		case 4:
			M.at(movieid).addFour();
			break;
		case 5:
			M.at(movieid).addFive();
			break;
		default:
			cout << " not a valid rating";
		}
	}
	cout << k << endl << endl;
	return R;

}


// SOLVES THE PART-------------------------1
void part1(vector <Movie> m)
{
	
	cout << ">> Top-10 Movies <<" << endl << endl;
	cout << "Rank\tID\tReviews\tAvg\tName" << endl;

		for (int i = 1; i <= 10; i++)
		{
			cout << i << ". \t" << m[i - 1].getmovieID() << "\t" << m[i - 1].getNumReviews() << "\t" << m[i - 1].getAverage() << "\t'" << m[i - 1].getmovieName()  <<"'"<< endl;
		}
		cout <<endl;
}

// SOLVES THE PART-------------------------2
void part2(map <int, Movie>  M, map <int, Review> R)
{
	cout << ">> Movie and Review Information <<" << endl;
	cout << "Please enter a movie ID (<100,000), a review ID (>= 100,000), 0 to stop>" << endl;

	long int userInput = 0; // Variable that user inputs to find movie or review.

	cin >> userInput;

	// USER INTERACTIVE LOOP.
	while (userInput != 0)
	{
		if (userInput < 0)
			cout << "**invalid id..." << endl;
		else if (userInput < 100000)
		{
			auto iter = M.find(userInput);

			if (iter == M.end())
				cout << "movie not found..." << endl;
			else
				M.at(userInput).print();		
		}

		else if (userInput >= 100000)
		{
			auto iter = R.find(userInput);

			 if ( iter == R.end())
				 cout << "review not found..." << endl;
			 else
				 R.at(userInput).print(M);
		}

		cout << "Please enter a movie ID (<100,000), a review ID (>= 100,000), 0 to stop>" << endl;
		cin >> userInput;
	}

	if (userInput == 0)
		cout << "** DONE! **" << endl;
}

int main()
{
	cout << "** Netflix Movie Review Analysis **" << endl;
	//auto  beginTime = std::chrono::steady_clock::now();
	string  moviefile, reviewfile;

	cin >> moviefile;
	cin >> reviewfile;
	cout << moviefile << endl;
	cout << reviewfile << endl;
	cout << endl;

	cout << std::fixed;
	cout << std::setprecision(5);

	ifstream file(moviefile);
	if (!file.good())
	{
		cout << "cannot  open  file!" << endl;
		return  -1;
	}

	ifstream filee(reviewfile);
	if (!filee.good())
	{
		cout << "cannot  open  file!" << endl;
		return  -1;
	}


	// Step 1:  input and parse data into a Map of Movie objects and review objects:
	auto movies = InputMovies(moviefile);
	auto reviews = InputReviews(reviewfile, movies);

	// PART ------1
	// Transfer Map container to Vector container to use built sort algorithm.

	vector <Movie> m;   // Vector collection of movies.

	for ( map <int, Movie>::iterator it = movies.begin(); it != movies.end(); ++it) 
	{
		m.push_back(it->second);
	}

	// Build in "sort" algorithm.
	sort(m.begin(), m.end(), [](Movie m1, Movie m2) 
	{
		if (m1.getAverage() > m2.getAverage())
			return true;
		else if (m1.getAverage() < m2.getAverage())
			return false;
		else
			if (m1.getmovieName() < m2.getmovieName())
				return true;
			else
				return false;
	}
	);

	// Function calls to solve the part1 and part2.
	part1(m);
	part2(movies, reviews);

	system("pause");
	return 0;
}

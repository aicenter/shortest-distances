#include "ProgressBar.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <mutex>

#define LENGTH_OF_PROGRESS_BAR 55
#define PERCENTAGE_BIN_SIZE (100.0/LENGTH_OF_PROGRESS_BAR)

namespace
{
	std::string generateProgressBar(unsigned int percentage)
	{
		const int progress = static_cast<int>(percentage / PERCENTAGE_BIN_SIZE);
		std::stringstream ss;
		ss << " " << std::setw(3) << std::right << percentage << "% ";
		std::string bar("[" + std::string(LENGTH_OF_PROGRESS_BAR - 2, ' ') + "]");

		unsigned int numberOfSymbols = (unsigned int) std::min(std::max(0, progress - 1), LENGTH_OF_PROGRESS_BAR - 2);

		bar.replace(1, numberOfSymbols, std::string(numberOfSymbols, '|'));

		ss << bar;
		return ss.str();
	}
}

ProgressBar::ProgressBar(size_t expectedIterations, const std::string& initialMessage)
	: mTotalIterations(expectedIterations),
	mNumberOfTicks(0),
	mEnded(false)
{
	std::cout << initialMessage << "\n";
	mLengthOfLastPrintedMessage = initialMessage.size();
	std::cout << generateProgressBar(0) << "\r" << std::flush;
}

ProgressBar::~ProgressBar()
{
	endProgressBar();
}

void ProgressBar::operator++()
{
	g_mutex.lock();
	if (mEnded)
	{
		throw std::runtime_error(
			"Attempted to use progress bar after having terminated it");
	}

	mNumberOfTicks = std::min(mTotalIterations, mNumberOfTicks + 1);
	const unsigned int percentage = static_cast<unsigned int>(
		(double) mNumberOfTicks * 100.0 / (double) mTotalIterations);

	std::cout << generateProgressBar(percentage) << "\r" << std::flush;
	g_mutex.unlock();
}

void ProgressBar::printNewMessage(const std::string& message)
{
	if (mEnded)
	{
		throw std::runtime_error(
			"Attempted to use progress bar after having terminated it");
	}

	std::cout << "\r"
		<< std::left
		<< std::setw(LENGTH_OF_PROGRESS_BAR + 6)
		<< message << "\n";
	mLengthOfLastPrintedMessage = message.size();
	const unsigned int percentage = static_cast<unsigned int>(
		(double) mNumberOfTicks * 100.0 / (double) mTotalIterations);

	std::cout << generateProgressBar(percentage) << "\r" << std::flush;

}

void ProgressBar::updateLastPrintedMessage(const std::string& message)
{
	if (mEnded)
	{
		throw std::runtime_error(
			"Attempted to use progress bar after having terminated it");
	}

	std::cout << "\r\033[F"
		<< std::left
		<< std::setw((int) mLengthOfLastPrintedMessage)
		<< message << "\n";
	mLengthOfLastPrintedMessage = message.size();
}

void ProgressBar::endProgressBar()
{
	if (!mEnded)
	{
		std::cout << std::string(2, '\n');
	}
	mEnded = true;
}

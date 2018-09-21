#pragma once

#include <string>

std::string FindAndReplaceAll(std::string str,
		const std::string &fnd,
		const std::string &rpl);
// Helper function to search a string for a certain substring
// an replace all occurrences with a replacement-string
// str - input sting that is being searched
// fnd - substring that is searched for
// rpl - substring that will replace fnd
// return value is a new string with replacements


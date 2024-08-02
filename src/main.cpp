#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <iomanip>


int main(int argC, char* argV[])
{
	std::filesystem::path inputFilePath;
	std::filesystem::path outputFilePath;
	std::string outputFileFormat;

	// check number of arguments
	if (argC != 3 && argC != 4)
	{
		std::cout << "error: invalid number of arguments!" << std::endl;
		std::cout << "usage: bin2hex <input file> -mem [<output file>]" << std::endl;
		std::cout << "usage: bin2hex <input file> -coe [<output file>]" << std::endl;
		return -1;
	}

	inputFilePath = argV[1];
	outputFileFormat = argV[2];

	if (outputFileFormat != "-mem" && outputFileFormat != "-coe")
	{
		std::cout << "error: invalid output file format!" << std::endl;
		return -1;
	}

	// input path only
	if (argC == 3)
	{
		// output path equals input path with replaced/appended file extension
		outputFilePath.replace_extension(outputFileFormat.substr(1));
	}
	// input and output path
	else if (argC == 4)
		outputFilePath = argV[3];

	// open input file
	std::ifstream inputFile(inputFilePath, std::ios::binary);
	if (!inputFile.is_open())
	{
		std::cout << "error: cannot open input file " << inputFilePath << "!" << std::endl;
		return -1;
	}
	// read input file into vector
	std::vector<char> data{ std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>() };
	inputFile.close();

	// make sure data is word aligned
	while (data.size() % 4 != 0)
		data.push_back(0x00);

	// open output file
	std::ofstream outputFile(outputFilePath, std::ios::trunc);
	if (!outputFile.is_open())
	{
		std::cout << "error: cannot open or create output file " << outputFilePath << "!" << std::endl;
		return -1;
	}

	// start the conversion
	std::cout << "generating " << outputFilePath << "..." << std::endl;

	if (outputFileFormat == "-coe")
	{
		outputFile << "memory_initialization_radix=16;" << std::endl;
		outputFile << "memory_initialization_vector=" << std::endl;
	}

	for (unsigned int i = 0; i < data.size(); i += 4)
	{
		outputFile << std::hex << std::setfill('0') << std::setw(8)
			<< *reinterpret_cast<uint32_t*>(&data.at(i));

		if (outputFileFormat == "-coe")
		{
			if (i != data.size() - 4)
				outputFile << ',' << std::endl;
			else
				outputFile << ';';
		}
		else if (i != data.size() - 4)
			outputFile << std::endl;
	}

	std::cout << "done." << std::endl;

	outputFile.close();
	return 0;
}

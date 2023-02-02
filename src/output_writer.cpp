#include "output_writer.hpp"
#include <string>
#include <ostream>

std::string inout_to_string(Input i)
{
	return std::to_string(i.nodeID) + ":" + std::to_string(i.value);
}

bool output_write(std::ostream& stream, const std::vector<InputLine>& input, const std::vector<OutputLine>& output)
{
	if(input.size() != output.size())
	{
		return false;
	}

	for(size_t i = 0; i < input.size(); i++)
	{
		const auto& in_line = input[i];
		const auto& out_line = output[i];

		// Write inputs
		stream << "IN: ";
		for(const auto& in : in_line)
		{
			stream << inout_to_string(in) << " ";
		}

		// Write outputs
		stream << "OUT: ";
		for(const auto& out : out_line)
		{
			stream << inout_to_string(out) << " ";
		}

		stream << std::endl;
	}

	return true;
}
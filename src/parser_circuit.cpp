#include "parser_circuit.hpp"
#include <fstream>
#include <string>
#include <sstream>

GateType get_type(const std::string& str)
{
	if(str == "IN:")
	{
		return GateType::INPUT;
	}
	else if(str == "OUT:")
	{
		return GateType::OUTPUT;
	}
	else if(str == "AND")
	{
		return GateType::AND;
	}
	else if(str == "NAND")
	{
		return GateType::NAND;
	}
	else if(str == "OR")
	{
		return GateType::OR;
	}
	else if(str == "NOR")
	{
		return GateType::NOR;
	}
	else if(str == "XOR")
	{
		return GateType::XOR;
	}
	else if(str == "XNOR")
	{
		return GateType::XNOR;
	}
	else if(str == "NEG")
	{
		return GateType::NEG;
	}
	else
	{
		return GateType::UNDEFINED;
	}
}

std::vector<ParsedGate> get_circuit(const std::string& filename)
{
	std::vector<ParsedGate> result;
	std::string line;
	std::ifstream file(filename);
	if(!file)
	{
		return {};
	}

	size_t lineNumber = 0;
	while(std::getline(file, line))
	{
		ParsedGate new_gate;
		std::string gate_type;
		std::stringstream ss(line);

		ss >> gate_type;
		new_gate.type = get_type(gate_type);
		new_gate.lineNumber = lineNumber++;

		size_t id;
		while(ss >> id)
		{
			new_gate.nodes.push_back(id);
		}

		result.emplace_back(new_gate);
	}

	return result;
}
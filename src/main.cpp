/**
 * @file main.cpp
 *
 * @brief Parse command-line arguments, intialize structures and run the simulation
 *
 */

#include <cstdlib>
#include <iostream>
#include <ostream>
#include "gate.hpp"
#include "parser_circuit.hpp"

void print_help(const std::string& program_name, std::ostream& stream)
{
	stream << "Usage: " << program_name << "-u [FILE] -i [FILE] -o [FILE]" << std::endl
		<< "-u file containing a circuit" << std::endl
		<< "-i input file containing input states" << std::endl
		<< "-o output file containing output states" << std::endl;
}

/**
 * @brief Convert initially parsed vector of gates to a map containing these gates
 */
std::map<size_t, Gate> prepare_simulation(const std::vector<ParsedGate>& parsed_gates)
{
	std::map<size_t, Gate> result;

	for(const auto& gate : parsed_gates)
	{
		// Sanity checks
		if(gate.type == GateType::UNDEFINED)
		{
			std::cerr << "Circuit file line " << gate.lineNumber << ": Undefined gate" << std::endl;
			exit(EXIT_FAILURE);
		}

		if(gate.type != GateType::INPUT && gate.nodes.size() < 2)
		{
			std::cerr << "Circuit file line " << gate.lineNumber << ": Gate cannot have less than one input and one output" << std::endl;
			exit(EXIT_FAILURE);
		}

		if(gate.type == GateType::NEG && gate.nodes.size() > 2)
		{
			std::cerr << "Circuit file line " << gate.lineNumber << ": Gate NEG cannot have more than one input" << std::endl;
			exit(EXIT_FAILURE);
		}

		// Add the gate to the map
		Gate new_gate;
		new_gate.type = gate.type;
		new_gate.inputs = {gate.nodes.begin(), gate.nodes.end()-1};
		new_gate.value = GateValue::UNDEFINED;

		result.emplace(gate.nodes.back(), new_gate);
	}

	return result;
}

void simulate_circuit(const std::map<size_t, Gate>& nodes)
{

}

int main(int argc, char* argv[])
{
	// Get arguments from the command line
	std::string circuit_file, input_file, output_file;

	// If the required arguments were not given, print help message and exit
	if(circuit_file.empty() || input_file.empty() || output_file.empty())
	{
		print_help(argv[0], std::cerr);
		exit(EXIT_FAILURE);
	}
}
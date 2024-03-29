/**
 * @file simulator.cpp
 *
 * @brief Parse command-line arguments, intialize structures and run the simulation
 *
 */

#include <cstdlib>
#include <ios>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "gate.hpp"
#include "parser_circuit.hpp"
#include "parser_input.hpp"
#include "simulator.hpp"
#include "output_writer.hpp"

typedef std::vector<size_t> OutputIDs;

/**
 * @brief Display help message
 */
void print_help(const std::string& program_name, std::ostream& stream)
{
	stream << "Usage: " << program_name << " -u [FILE] -i [FILE] -o [FILE]" << std::endl
		<< "-u file containing a circuit" << std::endl
		<< "-i input file containing input states" << std::endl
		<< "-o output file containing output states" << std::endl;
}

/**
 * @brief Convert initially parsed vector of gates to a map containing these gates
 *
 * @param[in]	parsed_gates	Vector of unprocessed gates
 *
 * @return
 *			- first: Map with the whole circuit
 *			- second: Vector with IDs of output nodes
 */
std::pair<std::map<size_t, Gate>, const OutputIDs> prepare_simulation(const std::vector<ParsedGate>& parsed_gates)
{
	std::map<size_t, Gate> result;
	OutputIDs outputs;

	for(const auto& gate : parsed_gates)
	{
		// Sanity checks
		if(gate.type == GateType::UNDEFINED)
		{
			std::cerr << "Circuit file line " << gate.lineNumber << ": Undefined gate" << std::endl;
			exit(EXIT_FAILURE);
		}

		if((gate.type != GateType::INPUT && gate.type != GateType::OUTPUT) && gate.nodes.size() < 2)
		{
			std::cerr << "Circuit file line " << gate.lineNumber << ": Gate cannot have less than one input and one output" << std::endl;
			exit(EXIT_FAILURE);
		}

		if((gate.type == GateType::NEG || gate.type == GateType::OUTPUT) && gate.nodes.size() > 2)
		{
			std::cerr << "Circuit file line " << gate.lineNumber << ": Gate NEG and output cannot have more than one input" << std::endl;
			exit(EXIT_FAILURE);
		}

		// Add the gate to the map
		Gate new_gate;
		new_gate.type = gate.type;
		new_gate.value = GateValue::UNDEFINED;

		if(new_gate.type == GateType::INPUT)
		{
			for(size_t id : gate.nodes)
			{
				result.emplace(id, new_gate);
			}
		}
		else if(new_gate.type == GateType::OUTPUT)
		{
			for(size_t id : gate.nodes)
			{
				outputs.emplace_back(id);
			}
		}
		else
		{
			new_gate.inputs = {gate.nodes.begin(), gate.nodes.end()-1};
			result.emplace(gate.nodes.back(), new_gate);
		}
	}

	return {result, outputs};
}

/**
 * @brief Resolve the outputs in the circuit
 *
 * @param[in]	nodes	Map of all logic gates
 *
 * @param[in]	input	Values of the input nodes
 *
 * @param[in]	outputs	Vector containing IDs of output nodes
 *
 * @return
 *			- success: Non-empty vector of output values
 *			- failure: Empty vector
 */
OutputLine simulate_circuit(std::map<size_t, Gate> nodes, const InputLine& input, const std::vector<size_t>& outputs)
{
	OutputLine result;

	// Set the values of the inputs
	for(const auto& in : input)
	{
		if(nodes.find(in.nodeID) != nodes.end())
		{
			nodes.at(in.nodeID).value = (in.value ? GateValue::ONE : GateValue::ZERO);
		}
		else
		{
			std::cerr << "Error: Input '" << in.nodeID << "' does not exist. Aborting" << std::endl;
			return {};
		}
	}

	for(size_t out : outputs)
	{
		GateValue value = GateValue::UNDEFINED;
		
		if(nodes.find(out) != nodes.end())
		{
			value = get_gate_value(nodes.at(out), nodes);
		}

		if(value == GateValue::UNDEFINED)
		{
			std::cerr << "Error while processing output '" << out << "'. Aborting" << std::endl;
			return {};
		}

		result.push_back({out, value == GateValue::ONE ? true : false});
	}

	return result;
}

/**
 * @brief Helper function used for extracting option argument from the argument vector
 */
std::string get_optarg(int& index, int argc, char* argv[])
{
	if(++index >= argc)
	{
		return {};
	}

	return argv[index];
}

int simulate(int argc, char* argv[])
{
	// Get the arguments from the command line
	std::string circuit_file, input_file, output_file;

	for(int i = 1; i < argc; i++)
	{
		std::string current_arg(argv[i]);
		std::string optarg = get_optarg(i, argc, argv);

		if(current_arg == "-u")
		{
			circuit_file = optarg;
		}
		else if(current_arg == "-i")
		{
			input_file = optarg;
		}
		else if(current_arg == "-o")
		{
			output_file = optarg;
		}
		else
		{
			print_help(argv[0], std::cerr);
			return -1;
		}
	}

	// If the required arguments were not given, print help message and exit
	if(circuit_file.empty() || input_file.empty() || output_file.empty())
	{
		print_help(argv[0], std::cerr);
		return -1;
	}

	// Prepare the environment
	auto input_lines = get_inputs(input_file);
	auto parsed_gates = get_circuit(circuit_file);
	auto[nodes, output_ids] = prepare_simulation(parsed_gates);
	std::vector<OutputLine> output;

	if(nodes.empty())
	{
		std::cerr << "Failed to create a map of the circuit" << std::endl;
		return -1;
	}

	// Simulate the circuit for different inputs
	for(const auto& input : input_lines)
	{
		auto output_line = simulate_circuit(nodes, input, output_ids);
		if(!output_line.empty())
		{
			output.emplace_back(output_line);
		}
	}

	// Write the output to the given file
	std::ofstream file(output_file);
	if(!file)
	{
		std::cerr << "Failed to open output file" << std::endl;
		return -1;
	}

	if(output_write(file, input_lines, output) == false)
	{
		std::cerr << "Error while writing to output file" << std::endl;
		return -1;
	}

	file.close();;

	return 0;
}
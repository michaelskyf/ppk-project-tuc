/**
 * @file parser_circuit.cpp
 *
 * @brief Functions and structures related to parsing the circuit file
*/

#pragma once

#include <cstddef>
#include <vector>
#include <string>
#include "gate.hpp"

/**
 * @brief Contains information about a specific gate/input (intermediate struct between text and struct Gate)
 */
struct ParsedGate
{
	size_t lineNumber;
	GateType type = GateType::UNDEFINED;
	std::vector<size_t> nodes;
};

/**
 * @brief Parse given file
 */
std::vector<ParsedGate> get_circuit(const std::string& filename);
#include "gate.hpp"
#include <stdexcept>
#include <vector>
#include <string>

bool get_value_and(const std::vector<bool>& inputs)
{
	for(bool input : inputs)
	{
		if(!input)
		{
			return false;
		}
	}

	return true;
}

bool get_value_nand(const std::vector<bool>& inputs)
{
	return !get_value_and(inputs);
}

bool get_value_or(const std::vector<bool>& inputs)
{
	for(bool input : inputs)
	{
		if(input)
		{
			return true;
		}
	}

	return false;
}

bool get_value_nor(const std::vector<bool>& inputs)
{
	return !get_value_or(inputs);
}

bool get_value_xor(const std::vector<bool>& inputs)
{
	bool is_odd = false;
	for(bool input : inputs)
	{
		if(input)
		{
			is_odd = !is_odd;
		}
	}

	return is_odd;
}

bool get_value_xnor(const std::vector<bool>& inputs)
{
	return !get_value_xor(inputs);
}

bool get_value_neg(const std::vector<bool>& inputs)
{
	return !inputs.front();
}

std::pair<bool, bool> get_value(GateType type, const std::vector<bool>& inputs)
{
	switch(type)
	{
		case GateType::AND:
		return { true, get_value_and(inputs) };

		case GateType::NAND:
		return { true, get_value_nand(inputs) };

		case GateType::OR:
		return { true, get_value_or(inputs) };

		case GateType::NOR:
		return { true, get_value_nor(inputs) };

		case GateType::XOR:
		return { true, get_value_xor(inputs) };

		case GateType::XNOR:
		return { true, get_value_xnor(inputs) };

		case GateType::NEG:
		return { true, get_value_neg(inputs) };

		default:
		return {false, 0};
	}
}

GateValue get_gate_value(Gate& gate, std::map<size_t, Gate>& nodes)
{
	std::vector<bool> input_values;

	// Return the value if it is already set
	if(gate.value != GateValue::UNDEFINED)
	{
		return gate.value;
	}

	// Collect all values from inputs
	for(size_t nodeID : gate.inputs)
	{
		if(nodes.find(nodeID) == nodes.end())
		{
			return GateValue::UNDEFINED;
		}

		GateValue v = get_gate_value(nodes.at(nodeID), nodes);

		// If at least one input is invalid, we can't get the value of current gate
		if(v == GateValue::UNDEFINED)
		{
			return GateValue::UNDEFINED;
		}

		input_values.push_back((bool)v);
	}

	// Return and set the value according to a gate type
	auto[is_valid, value] = get_value(gate.type, input_values);

	if(is_valid == false)
	{
		return GateValue::UNDEFINED;
	}

	if(value)
	{
		gate.value = GateValue::ONE;
	}
	else
	{
		gate.value = GateValue::ZERO;
	}

	return gate.value;
}

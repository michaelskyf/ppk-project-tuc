#include "gate.hpp"
#include <vector>

static bool get_value_and(const std::vector<bool>& inputs)
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

static bool get_value_nand(const std::vector<bool>& inputs)
{
	return !get_value_and(inputs);
}

static bool get_value_or(const std::vector<bool>& inputs)
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

static bool get_value_nor(const std::vector<bool>& inputs)
{
	return !get_value_or(inputs);
}

static bool get_value_xor(const std::vector<bool>& inputs)
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

static bool get_value_xnor(const std::vector<bool>& inputs)
{
	return !get_value_xor(inputs);
}

static bool get_value_neg(const std::vector<bool>& inputs)
{
	return !inputs.front();
}

static bool get_value(GateType type, const std::vector<bool>& inputs)
{
	switch(type)
	{
		case GateType::AND:
		return get_value_and(inputs);

		case GateType::NAND:
		return get_value_nand(inputs);

		case GateType::OR:
		return get_value_or(inputs);

		case GateType::NOR:
		return get_value_nor(inputs);

		case GateType::XOR:
		return get_value_xor(inputs);

		case GateType::XNOR:
		return get_value_xnor(inputs);

		case GateType::NEG:
		return get_value_neg(inputs);

		default:
		return UNDEFINED;
	}
}

GateValue get_gate_value(Gate& gate, std::map<size_t, Gate>& nodes)
{
	std::vector<bool> input_values;

	// Return the value if it is already set
	if(gate.value != UNDEFINED)
	{
		return gate.value;
	}

	// Collect all values from inputs
	for(size_t nodeID : gate.inputs)
	{
		GateValue v = UNDEFINED;
		try
		{
			v = get_gate_value(nodes.at(nodeID), nodes);
		}
		catch(...)
		{}

		// If at least one input is invalid, we can't get the value of current gate
		if(v == UNDEFINED)
		{
			return UNDEFINED;
		}

		input_values.push_back(v);
	}

	// Return and set the value according to a gate type
	bool value = get_value(gate.type, input_values);
	if(value)
	{
		gate.value = ONE;
	}
	else
	{
		gate.value = ZERO;
	}

	return gate.value;
}

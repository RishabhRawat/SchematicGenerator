#ifndef BOX_H
#define BOX_H
#include "common.h"
#include "moduleImpl.h"

/**
 * Box class is a container for modules, and comes below partitions in the partitioning heirarchy. A box is basically
 * a connected string of modules where the signal flow is unidirectional
 */
class box {
	friend class placement;
	friend class coreDesign;

private:
	partition* parentPartition;
	std::vector<moduleImpl*> boxModules;
	std::vector<std::pair<splicedTerminal*, splicedTerminal*>> boxLink;
	intPair offset, position, size;

public:
	/**
	 * Constructor to the class box
	 * @param m Pointer to the first module of the box
	 */
	box(moduleImpl* m) {
		m->setParentBox(this);
		boxModules.emplace_back(m);
	}
	/**
	 * Adds a module to the box
	 * @param m Pointer to the module being added
	 * @param src Pointer to the terminal of the last module in the box which connects it to this module
	 * @param sink Pointer to the terminal of this module which connects to the last module in the box
	 */
	void add(moduleImpl* m, splicedTerminal* src, splicedTerminal* sink);

	/**
	 * Sets the parent to this box
	 * @param p Pointer to the partition which will be set as parent partition
	 */
	void setParentPartition(partition* p) {
		parentPartition = p;
	}

	/**
	 * Calculate the length of the box, which is basically the number of modules contained inside
	 * @return Length of the box
	 */
	unsigned int length() const {
		return static_cast<unsigned int>(boxModules.size());
	}

	/**
	 * Fetches the position of the corners of the box, Call this function only after the placement has been done
	 * @param index The corner to be fetched, "0" indicated lower left and then moves anticlockwise
	 * @return returns coordinates of the requested corner
	 * @throw invalid argument error if index is not between 0 to 3
	 */
	intPair getVertex(const int index) {
		switch (index) {
			case 0:
				return position;
			case 1:
				return position + size.component(1);
			case 2:
				return position + size;
			case 3:
				return position + size.component(0);
			default:
				throw std::invalid_argument("Invalid index");
		}
	};
};

#endif  // BOX_H

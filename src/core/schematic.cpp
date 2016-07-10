#ifdef WEB_COMPILATION
#include "emscripten.h"
#include "emscripten/bind.h"
#endif
#include "schematic.h"
#include "coreDesign.h"

schematic::schematic() : pSchematicGenerator(new coreDesign(designParameters)) {}

void schematic::parseJsonFile(std::string jsonFile) {
	pSchematicGenerator->parseJsonFile(jsonFile);
}
void schematic::doPlacement() {
	pSchematicGenerator->doPlacement();
	pSchematicGenerator->doRouting();
}

std::string schematic::createDetailedJsonSchematicFromJson(std::string jsonData) {
	return pSchematicGenerator->createDebugJsonSchematicFromJson(jsonData);
}

std::string schematic::createJsonSchematicFromJson(std::string jsonData) {
	return pSchematicGenerator->createJsonSchematicFromJson(jsonData);
}
void schematic::doRouting() {
	pSchematicGenerator->doRouting();
}



#ifdef WEB_COMPILATION
EMSCRIPTEN_BINDINGS(schematic) {
	emscripten::class_<schematic>("schematic")
			.constructor<>()
			.function("createJsonSchematicFromJson", &schematic::createJsonSchematicFromJson)
			.function("createDetailedJsonSchematicFromJson", &schematic::createDetailedJsonSchematicFromJson)
			.function("doRouting",&schematic::doRouting);
}
#endif  // WEB_COMPILATION
#include "noesisInputHandler.h"

TypeHandle NoesisInputHandler::_type_handle;

NoesisInputHandler::NoesisInputHandler(const std::string &name)
    : DataNode(name) {}

NoesisInputHandler::~NoesisInputHandler() {}

void NoesisInputHandler::do_transmit_data(DataGraphTraverser *trav,
                                          const DataNodeTransmit &input,
                                          DataNodeTransmit &output) {}

void NoesisInputHandler::process(Noesis::IView *view) {}

/*
 * XMLException.h
 *
 *  Created on: 2013/02/20
 *      Author: mugwort_rc
 */

#ifndef XMLEXCEPTION_H_
#define XMLEXCEPTION_H_

namespace pyxerces {

void XMLException_init(void);

#define MakePythonTranslateXMLException(theType) \
PyObject* pyXerces##theType##Type = nullptr; \
\
void translate##theType(const xercesc::theType& e) { \
	assert(pyXerces##theType##Type != nullptr); \
	boost::python::object instance(e); \
	PyErr_SetObject(pyXerces##theType##Type, instance.ptr()); \
}


#define MakePythonXMLException(theType) \
auto theType = boost::python::class_<xercesc::theType, boost::python::bases<xercesc::XMLException> >(#theType, boost::python::init<const char* const, const XMLFileLoc, const xercesc::XMLExcepts::Codes, boost::python::optional<xercesc::MemoryManager* const> >()) \
		.def(boost::python::init<const char* const, const XMLFileLoc, const xercesc::XMLExcepts::Codes, const XMLCh* const, boost::python::optional<const XMLCh* const, const XMLCh* const, const XMLCh* const, xercesc::MemoryManager* const> >()) \
		.def(boost::python::init<const char* const, const XMLFileLoc, const xercesc::XMLExcepts::Codes, const char* const, boost::python::optional<const char* const, const char* const, const char* const, xercesc::MemoryManager* const> >()) \
		.def("duplicate", &xercesc::theType::duplicate, boost::python::return_value_policy<boost::python::reference_existing_object>()) \
		.def("getType", &xercesc::theType::getType, boost::python::return_value_policy<boost::python::return_by_value>()) \
		; \
pyXerces##theType##Type = theType.ptr(); \
boost::python::register_exception_translator<xercesc::theType>(&translate##theType);

} /* namespace pyxerces */
#endif /* XMLEXCEPTION_H_ */

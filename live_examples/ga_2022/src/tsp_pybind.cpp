#include <pybind11/pybind11.h>
#include <ga_opt.h>
#include <travel.h>

namespace py = pybind11;

PYBIND11_MODULE(tsp_pb, m) {
    py::class_<Travel>(m, "Travel")
        .def(py::init<>())
        .def("load", &Travel::load)
        .def("randomize", &Travel::randomize)
        .def("crossAndMutate", &Travel::crossAndMutate)
        .def("plot", &Travel::plot)
        .def("print", &Travel::print);
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}

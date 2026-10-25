#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../core/Window.h"
#include "../core/Renderer.h"

namespace py = pybind11;

PYBIND11_MODULE(renderer, m) {
    m.doc() = "C++ Core Engine Rendering module for 3D Character Creator";

    py::class_<Window>(m, "Window")
        .def(py::init<>())
        .def("init", &Window::Init)
        .def("should_close", &Window::ShouldClose)
        .def("swap_buffers", &Window::SwapBuffers)
        .def("poll_events", &Window::PollEvents)
        .def("shutdown", &Window::Shutdown);

    py::class_<Renderer>(m, "Renderer")
        .def(py::init<>())
        .def("initialize", &Renderer::Initialize)
        .def("clear", &Renderer::Clear)
        .def("render_triangle", &Renderer::RenderTriangle)
        .def("shutdown", &Renderer::Shutdown);
}

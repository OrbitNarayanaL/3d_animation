#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include "../core/Window.h"
#include "../core/Renderer.h"
#include "../core/Mesh.h"

namespace py = pybind11;

PYBIND11_MODULE(renderer, m) {
    m.doc() = "C++ Core Engine Rendering module for 3D Character Creator";

    py::class_<Vertex>(m, "Vertex")
        .def(py::init<>())
        .def_readwrite("position", &Vertex::position)
        .def_readwrite("normal", &Vertex::normal)
        .def_readwrite("texCoords", &Vertex::texCoords);

    py::class_<Mesh>(m, "Mesh")
        .def(py::init<>())
        .def_readonly("vertices", &Mesh::vertices)
        .def_readonly("indices", &Mesh::indices)
        .def("load_obj", &Mesh::LoadOBJ)
        .def("setup_mesh_buffers", &Mesh::SetupMeshBuffers)
        .def("shutdown", &Mesh::Shutdown);

    py::class_<Window>(m, "Window")
        .def(py::init<>())
        .def("init", &Window::Init)
        .def("should_close", &Window::ShouldClose)
        .def("swap_buffers", &Window::SwapBuffers)
        .def("poll_events", &Window::PollEvents)
        .def("shutdown", &Window::Shutdown);

    py::class_<Renderer>(m, "Renderer")
        .def(py::init<>())
        .def("initialize", py::overload_cast<const std::string&, const std::string&, const std::string&>(&Renderer::Initialize), py::arg("vertexShaderPath"), py::arg("fragmentShaderPath"), py::arg("objPath") = "")
        .def("clear", &Renderer::Clear)
        .def("render_triangle", &Renderer::RenderTriangle)
        .def("shutdown", &Renderer::Shutdown);
}

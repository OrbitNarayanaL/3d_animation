#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/glm.h>
#include "../core/Window.h"
#include "../core/Renderer.h"
#include "../core/Mesh.h"
#include "../core/Rigging.h"
#include "../core/SceneIO.h"

namespace py = pybind11;

PYBIND11_MODULE(renderer, m) {
    m.doc() = "C++ Core Engine Rendering module for 3D Character Creator";

    py::class_<Vertex>(m, "Vertex")
        .def(py::init<>())
        .def_readwrite("position", &Vertex::position)
        .def_readwrite("normal", &Vertex::normal)
        .def_readwrite("texCoords", &Vertex::texCoords)
        .def_readwrite("boneIds", &Vertex::boneIds)
        .def_readwrite("boneWeights", &Vertex::boneWeights);

    py::class_<Joint>(m, "Joint")
        .def(py::init<>())
        .def_readwrite("name", &Joint::name)
        .def_readwrite("index", &Joint::index)
        .def_readwrite("parentIndex", &Joint::parentIndex)
        .def_readwrite("localTransform", &Joint::localTransform)
        .def_readwrite("inverseBindTransform", &Joint::inverseBindTransform)
        .def_readwrite("globalTransform", &Joint::globalTransform);

    py::class_<Skeleton>(m, "Skeleton")
        .def(py::init<>())
        .def_readwrite("joints", &Skeleton::joints)
        .def("update_joint_transforms", &Skeleton::UpdateJointTransforms)
        .def("add_joint", &Skeleton::AddJoint)
        .def("compute_inverse_bind_matrices", &Skeleton::ComputeInverseBindMatrices);

    py::class_<BlendShape>(m, "BlendShape")
        .def(py::init<>())
        .def_readwrite("name", &BlendShape::name)
        .def_readwrite("offsets", &BlendShape::offsets);

    py::class_<Mesh>(m, "Mesh")
        .def(py::init<>())
        .def_readonly("vertices", &Mesh::vertices)
        .def_readonly("indices", &Mesh::indices)
        .def_readwrite("selected_vertex_index", &Mesh::m_selectedVertexIndex)
        .def("load_obj", &Mesh::LoadOBJ)
        .def("setup_mesh_buffers", &Mesh::SetupMeshBuffers)
        .def("shutdown", &Mesh::Shutdown)
        .def("find_closest_vertex_ray", &Mesh::FindClosestVertexRay)
        .def("deform_selected_vertex", &Mesh::DeformSelectedVertex)
        .def("apply_sculpt_brush", &Mesh::ApplySculptBrush)
        .def("recalculate_normals", &Mesh::RecalculateNormals)
        .def("add_blend_shape", &Mesh::AddBlendShape)
        .def("set_blend_shape_weight", &Mesh::SetBlendShapeWeight)
        .def("update_morph_geometry", &Mesh::UpdateMorphGeometry);

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
        .def("shutdown", &Renderer::Shutdown)
        .def("set_blend_shape_weight", [](Renderer& self, const std::string& name, float weight) { self.GetMesh().SetBlendShapeWeight(name, weight); })
        .def("set_albedo_color", &Renderer::SetAlbedoColor)
        .def("set_roughness", &Renderer::SetRoughness)
        .def("set_metalness", &Renderer::SetMetalness)
        .def("set_visualize_uv", &Renderer::SetVisualizeUV)
        .def_property_readonly("skeleton", [](Renderer& self) -> Skeleton& { return self.GetSkeleton(); })
        .def_property_readonly("mesh", [](Renderer& self) -> Mesh& { return self.GetMesh(); });

    m.def("save_scene", &SceneIO::SaveScene);
    m.def("load_scene", &SceneIO::LoadScene);
    m.def("export_mesh_to_obj", &SceneIO::ExportMeshToOBJ);
}

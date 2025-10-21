# USD Dependency Viewer

<p align="center">
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" />
  <img src="https://img.shields.io/badge/Qt-41CD52?style=for-the-badge&logo=qt&logoColor=white" />
</p>

A modern **C++ & Qt application** for exploring, visualizing, and managing **USD (Universal Scene Description) asset dependencies**.  
Built for VFX and animation pipelines where understanding complex USD hierarchies is critical.
> [!NOTE]
> Early wip

---

## Features

- **Dependency Graph Visualization**

  - Render intuitive graphs of USD file dependencies (references, payloads, sublayers).
  - Easily trace which assets depend on which sources.

- **Asset Management**

  - GUI based Asset Management system.
  - Metadata browsing, version tracking, and search.

- **Pipeline Management**  
  Manage your USD asset pipeline:

  - Detect broken/missing references
  - Validate dependencies against studio conventions

- **Search & Filtering**  
  Quickly locate assets by name, type, or dependency depth.

## Build Dependencies

### Fedora
```bash
usd-devel
python3-devel
imath-devel

double-conversion-devel
alembic-devel
hdf5-devel
draco-devel
openshadinglanguage-devel
OpenImageIO-devel
opensubdiv-devel
openvdb-devel
ptex-devel
OpenColorIO-devel
embree-devel
lz4-devel
libavif-devel
```

### Arch
WIP

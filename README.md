# cad-dwg

MIT reader for AutoCAD DWG geometry, written to be contributed to [GDAL](https://gdal.org/)'s open CAD driver.

This repository is a side project. It is not part of [GratisGIS](https://github.com/palavido-dev/gratis-gis).

## Status

The library identifies the DWG version from the six-byte magic at the start of the file (`AC1015`, `AC1018`, and the other codes listed below). It does not decode entities yet. A file that only has the right magic is not a drawing this library can turn into lines.

GDAL already reads DWG R2000 (`AC1015`) with the in-tree CAD driver (`libopencad`). That driver rejects every newer version. The first geometry target here is R2004 (`AC1018`), which is the first version that driver does not open.

## What a finished reader is for

A map. The intended result matches GDAL's DXF driver, not a CAD screen:

- one layer of entities
- layer name, text, and entity handle kept
- arcs and circles stroked to lines
- block inserts expanded one level when that can be done safely
- no coordinate system invented (DWG drawings usually have none)
- a count of entities that were skipped

Out of scope: writing DWG, hatches, solids, custom objects, and plot-faithful rendering.

## Versions recognized

| Magic | Name | Geometry in this repo |
| --- | --- | --- |
| `AC1012` | R13 | not started |
| `AC1014` | R14 | not started |
| `AC1015` | R2000 | use GDAL's existing CAD driver |
| `AC1018` | R2004 | next decoder |
| `AC1021` | R2007 | recognized only |
| `AC1024` | R2010 | recognized only |
| `AC1027` | R2013 | recognized only |
| `AC1032` | R2018 | recognized only |

## Build

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Requires CMake 3.16+ and a C11 compiler. GDAL is not required to build or test this tree.

## Upstream

A large driver addition to GDAL needs an RFC ([RFC 85](https://gdal.org/en/latest/development/rfc/rfc85_policy_code_additions.html), [RFC process](https://gdal.org/en/latest/development/rfc_process.html)). The draft in `docs/rfc-draft.md` has not been sent to gdal-dev and has not been opened as a GDAL pull request.

The short name `DWG` in GDAL is the optional Open Design Alliance driver. This project must not take that name. The open driver to extend is `CAD`.

## License

[MIT](LICENSE). That is the license GDAL can merge ([GDAL's license](https://gdal.org/en/latest/license.html)). See [CONTRIBUTING.md](CONTRIBUTING.md) for the rules on what source may be used.

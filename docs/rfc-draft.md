# RFC draft: read DWG versions after R2000 in the open CAD driver

Status: **draft, not submitted.** This file is not a GDAL pull request and has not been mailed to gdal-dev.

| | |
| --- | --- |
| Author | Matt Palavido |
| Contact | matthew@gratisgis.org |
| License of the proposed code | MIT, for inclusion under GDAL's MIT license |
| Started | 2026-11-08 |

## Summary

Extend GDAL's existing open `CAD` driver so it can read common geometry from DWG versions newer than R2000. Do not replace the optional Open Design Alliance `DWG` driver. Do not write DWG.

## Motivation

The in-tree CAD driver (vendored libopencad) opens `DWG_R2000` only. `GetCADFormats()` reports `DWG R2000 [ACAD1015]`, and every other version returns unsupported. Current drawings saved by AutoCAD, BricsCAD, and Civil 3D are newer than that, so an open GDAL build cannot read them.

People doing GIS work need lines, polylines, arcs, circles, text, and block inserts on their layers. They do not need a CAD kernel. GDAL's DXF driver already defines that shape: one `entities` layer, a few generic attributes, curves stroked, and no coordinate system unless the file has one. DWG files generally have none.

## Proposed behavior

- Driver short name stays `CAD`. The `DWG` short name stays the optional ODA build.
- Read only.
- First version to add: R2004 (`AC1018`). Further versions (R2007, R2010, R2013, R2018) follow one at a time, each with its own tests.
- Entities: line, lightweight polyline, polyline, arc, circle, text/mtext (as a point plus a text attribute), and a block insert expanded one level when the block is present.
- Other entities are skipped and counted. The dataset still opens.
- Attributes align with the DXF driver where that is honest: Layer, Text, EntityHandle. Color and line type can follow later.
- No CRS is assigned. Callers pass `-s_srs` when they know the drawing's coordinates, the same way a DXF without a CRS is handled.
- `Open()` / `Identify()` stay selective. A file whose magic is not a known DWG version is refused. A truncated file fails cleanly.

The version probe that exists today lives in the side repository [cad-dwg](https://github.com/palavido-dev/cad-dwg). It does not decode entities.

## What this RFC does not do

- It does not link LibreDWG. That library is GPL-3.0-or-later, which GDAL's MIT tree does not take.
- It does not vendor ODA/Teigha.
- It does not change the ODA `DWG` driver.
- It does not promise visual fidelity (hatches, fills, dimensions as drawn, ACIS solids, proxy objects, xrefs that are not in the file).

## Backward compatibility

R2000 behavior of the current CAD driver stays. New versions are additive. Applications that only call the driver when it opens a file gain newer files. The ODA driver's short name and options stay as they are.

## Security

DWG parsers are a common fuzz target. The decoder must reject truncated section maps without reading off the buffer. Tests include truncated files. The driver stays optional in spirit: a build that does not want the open CAD reader can keep omitting it the way it can today. Fuzzing against the new version path is part of the implementation, not a follow-up.

## Testing

- Synthetic and tiny redistributable fixtures only.
- One test per version magic, including rejection of a short buffer and of a non-DWG.
- For R2004: one line, one arc or circle (stroked), one text, one insert, and one unsupported entity that increments the skip count.
- `test_ogrsf` once the code is in the GDAL tree.
- No dependence on a proprietary SDK in CI.

## Documentation

Update the CAD driver page. State the versions actually read, that the file has no CRS, and which entity types are skipped. Point writers of modern DWG who need full fidelity at the separate ODA-enabled driver, without describing this reader as that driver.

## Maintenance

The author is willing to be the maintainer recorded for this driver under RFC 85: tests, docs, bug triage, and keeping the code building when GDAL's surrounding tools change.

## Related

- GDAL CAD driver and vendored libopencad (`ogr/ogrsf_frmts/cad`), R2000 only.
- GDAL DXF driver, the behavior model.
- GDAL DWG driver page, which documents the ODA build and the "no georeferencing" rule.
- RFC 85 (substantial additions) and RFC 3 (license and the right to contribute).

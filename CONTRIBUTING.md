# Contributing

This tree is MIT so it can be offered to GDAL. GDAL's committers have to be able to see that contributed code is under that license and that the contributor has the right to submit it ([RFC 3](https://gdal.org/en/stable/development/rfc/rfc3_commiters.html)).

By sending a patch you agree that your contribution is available under the MIT license in `LICENSE`, and that you have the right to do that (including your employer's approval when the work is not yours alone).

## Source you must not copy

- LibreDWG and other GPL code. GDAL is MIT and does not take GPL into the tree. Do not translate GPL code into this repository either.
- Open Design Alliance / Teigha headers, samples, and source. Do not paste them here.
- Proprietary DWG files you do not have rights to redistribute. Tests need tiny files we can commit, or synthetic bytes.

MIT code may be adapted if its copyright notice and license stay with the adaptation. [ACadSharp](https://github.com/DomCR/ACadSharp) is MIT and is C#. A port of a geometry subset would keep that copyright notice. Read it on purpose, in a separate session from any GPL DWG source, and record the files you used in the commit message.

## What to add next

R2004 (`AC1018`) geometry only: line, lightweight polyline, polyline, arc, circle, text, and a single-level block insert. Skip everything else and count the skips. Do not add a writer.

Tests should be movable into GDAL's `autotest/ogr` suite later: small inputs, expected geometry, expected skips. Match GDAL's C++ style when a pull request to GDAL is actually prepared. This repository can stay simple until then.

## Maintainer

Matt Palavido. A GDAL driver needs a named maintainer who answers bugs ([RFC 85](https://gdal.org/en/latest/development/rfc/rfc85_policy_code_additions.html)). Opening the upstream RFC is a separate step from committing here.

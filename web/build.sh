#!/bin/sh
# Compila o núcleo C++ para WebAssembly e monta o site em web/dist.
# Requer o Emscripten (brew install emscripten). Uso: sh web/build.sh

set -e

RAIZ="$(cd "$(dirname "$0")/.." && pwd)"
SAIDA="$RAIZ/web/dist"

rm -rf "$SAIDA"
mkdir -p "$SAIDA"
cp -R "$RAIZ/web/public/." "$SAIDA/"

em++ -std=c++20 -O2 \
    -I"$RAIZ/Core" \
    "$RAIZ/Core/CartasCore.cpp" "$RAIZ/web/bindings.cpp" \
    -lembind \
    -sMODULARIZE=1 -sEXPORT_ES6=1 -sENVIRONMENT=web \
    -o "$SAIDA/cartas.js"

echo "Site gerado em $SAIDA"

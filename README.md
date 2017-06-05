__Assume-se para este tutorial que o computador configurado possui ambiente Linux e GCC instalado.__

Simulador de uma cache para um CPU (ISA Hipotética)
========

```
* Main.c: Interface "gráfica" (BASH) do simulador
* Cache.h: Biblioteca de funções do simulador
* Cache.c: Funções matemáticas que implementam o simulador
```

Compilando o código fonte do simulador
-----------
```
gcc Cache.c Cache.h Main.c -o cache
```

Executando o simulador
-----------
```
./cache
```
Novas funcionalidades (Futuro):
-----------

- Adição de mapeamento direto e associativo por conjuntos
- Adiço de política de substituiço LRU e Random.
- Utilização de política de escrita WB.
- Interface gráfica pode ser construída utilizando Qt.

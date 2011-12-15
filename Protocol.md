## Serveur → Client

    [type:char][size:uint32][message:buffer(size)]

La taille indiquée est celle du message seulement.

- 'i': info
- 'e': error

## Client → Serveur

    [type:char][more data according to type…]

### type: 'i' init

    [type:char][nbPalette1:uint32][nbPalette2:uint32]

- nbPalette1: nombre de palettes de type 1.
- nbPalette2: nombre de palettes de type 2.

### type: 'c' command

    [type:char][nbPalette1:uint32][nbPalette2:uint32]

- nbPalette1: nombre de palettes de type 1.
- nbPalette2: nombre de palettes de type 2.

### type: 'a' answer

    [type:char][answer:char]

- answer: 'c' continue, 's' stop


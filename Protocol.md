## Server to Client

    [type:char][size:int32][message:buffer(size)]

The size indicated is that of the message only.

- 'i': info
- 'e': error

## Client to Server

    [type:char][more data according to type…]

### type: 'i' init

[Self-descriptive]

### type: 'c' command

    [type:char][numCommande:uint32][part_type:char][part_number:uint32][part_number_dif:int16]

- numCommande: numéro de la commande
- part\_type: 1, 2 (ou autre)
- part\_number: nombre de pièce de type part\_type
- part\_number\_dif: nombre de pièces différntes dans la commande

### type: 'a' answer

    [type:char][answer:char]

- answer: 'c' continue, 's' stop


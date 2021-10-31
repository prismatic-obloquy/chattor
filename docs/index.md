---
title: Home
description: An overview of Chattor, download links, and important usage info.
---

Chattor is an anonymized, distributed, and end-to-end encrypted chat system and social network.
It supports text chat, file transfer, and offline messages, all with public-key cryptography and as anonymous as you want yourself to be.
It's built on Tor's onion services, and gives back to the network by encouraging every user to run a Tor relay too.

Chattor is built on proven, tested privacy technology:
All communications are over Tor, keeping things encrypted and anonymous at the transport layer.
The public-key cryptography is all ECC based on Curve25519, and the symmetric encryption is AES-256-GCM.
Monero's Bulletproofs are used as well, in the single place they're required.
For more technical details, see [/protocol].

  [/protocol]: ./protocol/
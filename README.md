# Chattor

Chattor is an anonymized, distributed, and end-to-end encrypted chat system and social network.
It supports text chat, file transfer, and offline messages, all with public-key cryptography and as anonymous as you want yourself to be.
It's built on Tor's onion services, and gives back to the network by encouraging every user to run a Tor relay too.

The core of Chattor is a "peer-to-peer" network of onion services.
No direct connections are ever made -- it's called peer-to-peer because there's no central server mediating the chatter.
Each onion service is a user, and each user knows what's going on in their bit of the network.
When they get online, they'll ask the network what they missed, and thanks to asymmetric cryptography, people can tell them without having to know themselves.

Bear in mind that Chattor, like Tor, can't protect you from yourself.
If you post your name, phone number, and address publicly, none of Chattor's privacy features will help you.

> **Security warning**:
>
> Chattor is not a security product.
> It lets you have a Facebook-like experience, without the Facebook-like tracking, and it tries pretty hard to make sure people can't know anything you don't post publicly, without your approval.
>
> There isn't any good onion service crate in Rust yet.
> Accordingly, I've had to write my own.
> While I followed the spec closely and am an experienced programmer, the code has not (*yet*) been formally audited, tested, or validated.
>
> Similarly, the cryptography is built on solid, reviewed libraries: [`libhydrogen`] and [`bellman`].
> My use of them is not necessarily perfect.
>
> Use at your own risk.

## Architecture

Chattor is structured as a mesh network of 'nodes'.
Each node runs two Tor onion services, which are the way other nodes reference it.
The first is semipermanent, and acts as a direct connection point:
Anyone who knows it can send that user, if they're online, messages or friend requests directly.
The second is ephemeral, and is an anonymous handle to "someone in the network", who promises they have certain relationships with others in the network.

Each node has some 'friends'.
They're called that because Chattor is a social network, and thus most nodes marked as friends will be actual friends.
However, friendship in the architecture is just a limited trust relationship -- you trust your friends will take messages for you without dropping them, and not to deliberately disclose your identity.

And that's it.
The entire network is peer-to-peer, through Tor.
It deliberately allows things like mass relays and bots as simple nodes; while clients may treat them differently, to the protocol everything is nodes and friendships.


  [`libhydrogen`]: https://crates.io/crates/libhydrogen
  [`bellman`]: https://crates.io/crates/bellman

# Chattor v0.0.1

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
> Chattor is not a security product; it's a privacy product.
> It lets you have a Facebook-like experience, without the Facebook-like tracking, and it tries pretty hard to make sure people can't know anything you don't post publicly, without your approval.
> *To accomplish this*, it provides some measure of security; namely, protections against unauthorized people being able to read messages or distinguish associations.
> However, it's ultimately meant to be a privacy-respecting social network, and while you may find it useful for other purposes, you should take a close look at [the protocol][website-protocol] to make sure it meets your needs.
>
> The cryptography is built on solid principles and with well-reviewed implementations of primitives.
> However, Chattor hasn't (*yet*) been audited, and may be misusing the cryptography, or making stronger guarantees than actually hold.
> I'm confident I did things right, and trust Chattor myself, but until *someone else* has gone in and thoroughly reviewed it, I can't ethically recommend you trust it too.
>
> Finally: Don't let this scare you into avoiding Chattor.
> Let it scare you into making your own reasoned, educated decision about it.
> It's your privacy.
> **You** decide.

For details on the way this works, see `docs/` in the repo or [the website][chattor-clear-site] (also available in [onion][chattor-onion-site] form).

## FAQ

There are some common questions regarding Chattor, so here are the answers.

### If you're not paying for the product, you *are* the product. I'm not paying for Chattor. So what's the product here?

There isn't one.

Most companies, including most privacy systems, have to support massive infrastructure and many employees.
Costs can get extremely high, and they need to pay *somehow* -- so they either need to sell something to you, like Proton; be a nonprofit, like Signal; or sell *you* to something, like Facebook.

But if you could eliminate all the costs, you wouldn't need any financial support at all.
That's Chattor's trick.

There's no infrastructure.
Everything is built over Tor, which already exists, and there's no central server passing messages around.
That immediately removes almost all the infrastructure costs, and all that remains is the $20 or so a month for the main website -- which is small enough that I can pay for it on my own.

There are also no employees.
Everyone working on it is volunteering their time to it.
While this means we have slower turnaround time for bugs and features, it also means we don't need to come up with funding for any employees, so no one can threaten us by cutting funding off.

The end result is that there *is* no product here.
You don't need to worry about being it.

(Note this might not apply to your Chattor client -- expect them to provide their own guarantees.)

### What's stopping someone from just shutting Chattor down?

There's three potential readings of this question.

The first is simply, "What prevents someone from taking down Chattor's servers and disabling it?"
This is easy:
There *are* no servers.
There's nothing to shut down here.
The only 'weak link', so to speak, is the Tor network, which *can* be blocked.
Fortunately, Tor itself has defenses against this, and Chattor is compatible with all of them.

The seond is more complex: "What prevents someone from selectively blocking Chattor from being used?"
All traffic going over Tor is inherently encrypted and anonymized.
It's identifiable as Tor traffic, but it's impossible for anyone in the middle to tell whether it's Chattor, web browsing, or anything else going over Tor.
So there's no way to block Chattor differently from any other Tor usage.

The third is the most complex of all: "Why can't someone keep Chattor from being installed?"
Unfortunately, there's no cryptographic defense against megacorporations updating their proprietary ecosystems to ban privacy, as unlikely as that is.
If you live in an area where your right to privacy and true ownership of your device are guaranteed legally, you might have some legal recourse, and organizations like [EFF] can help.
The good news is that the Chattor spec and reference implementation are both fully open and rehostable, so as long as anyone has a copy, it can be republished.

### I already use Signal. Should I switch to Chattor?

First, read the security warning above.



### How exactly does Chattor work?

The specification is in `docs/protocol/` in the repository, or online [here][website-protocol].

You can also peruse the source code, if you can read C.
In fact, it's strongly encouraged.
The more eyes there are looking over the code, the less time bugs have before they're discovered.

### I like Chattor and want to help. How can I?

There are three things you can do:

1.  [Report any bugs][bug-report] you find.
    Just make sure they're actually related to something in this repo, and not your specific client.
2.  [Come up with features][feature-request] you think would be useful.
    The same disclaimer applies:
    The only client we'll add features to here is the reference one.
3.  [Pick up an issue][triaged-issues] and get it fixed.
    Please don't just directly implement features or fix what look like bugs -- give the devs a chance to deduplicate and prioritize issues.

If you find a security issue, please [see here][insecurity]

  [chattor-clear-site]: https://chattor.prismatic.obloquy.work/
  [chattor-onion-site]: https://chattor.prismatic.obloquy.work/ "Okay, not yet. Soon though!"
  [EFF]: https://www.eff.org/
  [website-protocol]: https://chattor.prismatic.obloquy.work/protocol
  [insecurity]: https://prismatic.obloquy.work/insecurity
  [bug-report]: 

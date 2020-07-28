# SimulVirus
Simple Virus Spread Simulator

Program that simulates the spread of a virus from a unique infected patient (patient zero) inside a completely naive population. It is based on the following basic assumptions:
- A person can infect another person only when incubating the virus
- Infected people stay in the incubating state for a constant period of time, then become sick and are isolated
- Infected people stay in the sick state for a constant period of time, then either die or become immune to the virus
- No test, treatment or vaccine exist for this virus

The following parameters are read on standard input:
- Initial population
- Infection rate
- Contacts (per person and unit of time)
- Incubation time
- Sick time
- Death rate
- Simulation time

The unit of time is called a "round".

At round 0, one person is in the incubating state. The remaining of the population is in the naive state (no one is sick, dead or immune). At each round, the following calculations are done:
- Round standing = Total naive + Total incubating + Total immune
- Round contacts = Total incubating * Contacts * Round standing / Initial population
- If Round contacts > Round standing then Round contacts = Round standing
- Round infected = Total naive / Round standing * Infection rate * Round contacts
- Round dead = Sick since "Sick time" rounds * Death rate
- Add "Round dead" to "Total dead"
- Round immune = Sick since "Sick time" rounds - Round dead
- Add "Round immune" to "Total immune"
- Incubating since "Incubation time" rounds shift in the Sick state
- "Round infected" shift in the Incubating state
- Subtract "Round infected" from "Total naive"
- Subtract "Round dead" from "Total alive"

The number of contacts will change at each round depending on the number of people still "standing" in proportion to the initial population. The state after each round is printed on the standard output in tab delimited format for future export in Excel or other analysis tool.

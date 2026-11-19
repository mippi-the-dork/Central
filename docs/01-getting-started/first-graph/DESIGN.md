# Your First Blueprint Graph — Design

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## Find and use a node

1. Open an Actor Blueprint, Widget Blueprint or another appropriate Blueprint graph.
2. Right-click in the graph and search **Mean Value** under **Math → Statistics**.
3. Add a **Make Array** node containing **2, 4, 6, 8** (Integer array).
4. Connect its array output to Central's **Values** input. The initially wildcard pin becomes typed from the connected array.
5. Read the result on **Value**: the average is **5.0**, and the Integer input produces a **Double** output.
6. Use **Has Value** before consuming the result. A false validity output means the default Value is not a valid statistic.

## Test the other operations

**Median:** Connect [1, 3, 5, 9, 100] to Median Value; it returns 5. Try [1, 2, 3, 4] to see the even-count result 2.5.

**Mode:** Connect [2, 2, 3, 3, 4] to Mode Value. `Value = 2`, `Modes = [2, 3]`, `Frequency = 2`, `Has Mode = true`.

**Weighted Mean:** Connect Values [10, 20] and a separate Double Weights array [1.0, 3.0]. The output is 17.5, Has Value true.

## Important editing behavior

The **Values input must be connected** to a supported array; it is not a free-entry array default. Use Make Array for constants. When replacing the connected array with another type, check downstream connections and compile the Blueprint again.

## What to avoid

Do not treat a zero result as necessarily invalid; zero may be the correct average. Do not assume an all-unique Mode input has a mode. Use its Has Mode output rather than relying on the Frequency pin alone.

---

[Technical implementation](TECHNICAL.md) · [All statistics nodes](../../02-statistics-nodes/README.md)

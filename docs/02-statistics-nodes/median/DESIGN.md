# Median Value — Design

**Central v1.0.0 · Unreal Engine 5.8.x · Runtime + Editor**

## What it calculates

Median finds the middle after ordering input values. For an odd number of values, the middle element is returned; for an even number, the two central values are averaged.

| Values | Median |
| --- | --- |
| [10, 3, 7] | 7 |
| [1, 2, 3, 4] | 2.5 |
| [1, 3, 5, 9, 100] | 5 |

## Blueprint pins

Values is a connected supported array; **Value** returns the median and **Has Value** says whether the result is valid.

## When Median is useful

Suppose measured input times are [12, 13, 14, 15, 130] milliseconds. The median is 14 and is less influenced by the extreme sample than the mean. Median is useful when you want the central tendency of an ordered dataset rather than the total divided by the count.

## Does it change my array?

<!-- Media target: Image | central-median | docs/assets/media/central-median.png -->
<figure class="doc-media" data-kind="image" data-media-id="central-median">
  <img src="../../assets/media-placeholder.svg" alt="Median orders temporary data without modifying the input array." loading="lazy">
  <figcaption>Median orders temporary data without modifying the input array.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture unsorted Values [10,3,7] with Median result 7 and a debug watch showing the original array order unchanged.</span></figcaption>
</figure>


No. Median sorts a **working copy** of the input, not the original Blueprint array. You can use the source array elsewhere without its elements being re-ordered.

## Even counts and mathematical structs

<!-- Media target: GIF | central-median-even | docs/assets/media/central-median-even.gif -->
<figure class="doc-media" data-kind="gif" data-media-id="central-median-even">
  <img src="../../assets/media-placeholder.svg" alt="Even-sized arrays average two middle values and complex types use components." loading="lazy">
  <figcaption>Even-sized arrays average two middle values and complex types use components.<span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record [1,2,3,4] giving Median 2.5, then demonstrate Vector Median as independent X/Y/Z calculations with visible outputs.</span></figcaption>
</figure>


Integer arrays return Double, allowing the two middle values to average to a fraction. For supported vectors/colors, Median is calculated independently for every coordinate/channel. It is **not** the geometric median, and the resulting vector may not exist among the original array elements.

## Invalid cases

Empty input and non-finite values produce Has Value false and a default output. Use the validity pin rather than comparing Value with zero.

---

[Technical implementation](TECHNICAL.md) · [All statistics nodes](../../02-statistics-nodes/README.md)

# Renderer2D Benchmarks

#### **Build:** Release
#### **Implementation:** Temporary sorting vector
#### **Algorithm:** std::stable_sort
#### **Measured:** DrawQuad + EndDraw
#### **Repetitions:** 5
#### **Date:** Oct 10, 2026

## Results

CPU Median (ms) | CV (%)

| Submissions | Single Layer | CV     | Multi Layer | CV   |
|-------------|--------------|--------|-------------|------|
| 1,000       | 0.051        | 0.91   | 0.055       | 1.44 |
| 10,000      | 0.858        | 4.19   | 0.950       | 2.39 |
| 50,000      | 8.904        | 1.36   | 7.155       | 3.08 |
| 100,000     | 13.300       | 9.99   | 15.157      | 2.33 |

## Notes

- CPU benchmark using stubbed graphics device.
- Temporary sorting vector selected after comparison.
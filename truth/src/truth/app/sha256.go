package sha

import (
  "fmt"
)

var (
  // Constants
  K = []int{
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
      }
  // Initial hash value
  H = []int{
        0x6a09e667,
        0xbb67ae85,
        0x3c6ef372,
        0xa54ff53a,
        0x510e527f,
        0x9b05688c,
        0x1f83d9ab,
        0x5be0cd19,
      }
)

func shr(x int, n uint) int {
  return (x >> n)
}

func rotr(x int, n uint) int {
  return (x >> n) | (x << (32-n))
}

func rotl(x int, n uint) int {
  return (x << n) | (x >> (32-n))
}
// CH( x, y, z) = (x AND y) XOR ( (NOT x) AND z)
func ch(x, y, z int) int {
  return (x & y) ^ (^x & z)
}

//MAJ( x, y, z) = (x AND y) XOR (x AND z) XOR (y AND z)
func maj(x, y, z int) int {
  return (x & y) ^ (x & z) ^ (y & z)
}

//bsig0(x) = ROTR^2(x) XOR ROTR^13(x) XOR ROTR^22(x)
func bsig0(x int) int {
  return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22)
}

//bsig1(x) = ROTR^6(x) XOR ROTR^11(x) XOR ROTR^25(x)
func bsig1(x int) int {
  return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25)
}

//ssig0(x) = ROTR^7(x) XOR ROTR^18(x) XOR SHR^3(x)
func ssig0(x int) int {
  return rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3)
}

//ssig1(x) = ROTR^17(x) XOR ROTR^19(x) XOR SHR^10(x)
func ssig1(x int) int {
  return rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10)
}

func nbyte(v int, n uint) int {
  loffs := 4 * n
  return ((v & (0xf << loffs)) >> loffs)
}

func set_byte(v *int, n uint, new_val int) {
  loffs := 4 * n
  *v = (*v) & (^(0xf << loffs))
  *v = (*v) | (new_val << loffs)
}

func padding(data []byte) []int {
  msg_len := len(data) * 8
  ret := make([]int, len(data))
  ret = append(ret, 0x10000000)

  for ;len(ret)*8 < 448 && 0 != (len(ret)*8) % 512; {
    ret = append(ret, 0x0)
  }

  ret[len(ret)-1] = ret[len(ret)-1] | msg_len
  return ret
}

func compute(M []int) []int {
  N := 16
  Hinit := H

  for i := 1; i < N; i++ {
    // Prepare the message schedule W:
    W := make([]int, 512)
    for u := uint(0); u < 16; u++ {
      W[u] = nbyte(M[i], u)
    }
    for u := 16; u < 64; u++ {
      W[u] = ssig1(W[u-2]) + W[u-7] + ssig0(u-15) + W[u-16]
    }

    // Initialize the working variables:
    a := nbyte(Hinit[i-1], 0)
    b := nbyte(Hinit[i-1], 1)
    c := nbyte(Hinit[i-1], 2)
    d := nbyte(Hinit[i-1], 3)
    e := nbyte(Hinit[i-1], 4)
    f := nbyte(Hinit[i-1], 5)
    g := nbyte(Hinit[i-1], 6)
    h := nbyte(Hinit[i-1], 7)

    // Perform the main hash computation:
    for u := 0; u < 64; u++ {
      t1 := h + bsig1(e) + ch(e,f,g) + K[u] + W[u]
      t2 := bsig0(a) + maj(a,b,c)
      h = g
      g = f
      f = e
      e = d + t1
      d = c
      c = b
      b = a
      a = t1 + t2
    }

    // Compute the intermediate hash value H(i):
    set_byte(&Hinit[i], 0, a + nbyte(Hinit[i-1], 0))
    set_byte(&Hinit[i], 1, a + nbyte(Hinit[i-1], 1))
    set_byte(&Hinit[i], 2, a + nbyte(Hinit[i-1], 2))
    set_byte(&Hinit[i], 3, a + nbyte(Hinit[i-1], 3))
    set_byte(&Hinit[i], 4, a + nbyte(Hinit[i-1], 4))
    set_byte(&Hinit[i], 5, a + nbyte(Hinit[i-1], 5))
    set_byte(&Hinit[i], 6, a + nbyte(Hinit[i-1], 6))
    set_byte(&Hinit[i], 7, a + nbyte(Hinit[i-1], 7))
   }
   return Hinit
 }

 func digest(data []byte) []int {
   pad := padding(data)
   return compute(pad)
 }
/**
 func main() {
   res := digest([]byte("comute with algorithm sha256"))
   fmt.Println(res)
 }
*/

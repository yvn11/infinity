package main

import (
  "fmt"
  "io/ioutil"
  "flag"
  "crypto/sha256"
)

var (
  MSGBLKSIZE256 = 64
  // Constants
  K = []uint32{
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
  H = []uint32{
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

func shr(x uint32, n uint32) uint32 {
  return (x >> n)
}

func rotr(x uint32, n uint32) uint32 {
  return (x >> n) | (x << (32-n))
}

func rotl(x uint32, n uint32) uint32 {
  return (x << n) | (x >> (32-n))
}

// CH( x, y, z) = (x AND y) XOR ( (NOT x) AND z)
func ch(x, y, z uint32) uint32 {
  return (x & y) ^ ((^x) & z)
}

//MAJ( x, y, z) = (x AND y) XOR (x AND z) XOR (y AND z)
func maj(x, y, z uint32) uint32 {
  return (x & y) ^ (x & z) ^ (y & z)
}

//bsig0(x) = ROTR^2(x) XOR ROTR^13(x) XOR ROTR^22(x)
func bsig0(x uint32) uint32 {
  return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22)
}

//bsig1(x) = ROTR^6(x) XOR ROTR^11(x) XOR ROTR^25(x)
func bsig1(x uint32) uint32 {
  return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25)
}

//ssig0(x) = ROTR^7(x) XOR ROTR^18(x) XOR SHR^3(x)
func ssig0(x uint32) uint32 {
  return rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3)
}

//ssig1(x) = ROTR^17(x) XOR ROTR^19(x) XOR SHR^10(x)
func ssig1(x uint32) uint32 {
  return rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10)
}

func nbyte(v uint32, n uint32) uint32 {
  loffs := 4 * n
  return ((v & (0xf << loffs)) >> loffs)
}

func set_byte(v *uint32, n uint32, new_val uint32) {
  loffs := 4 * n
  *v = (*v) & (^(0xf << loffs))
  *v = (*v) | (new_val << loffs)
}

func padding(data []byte) []byte {
  msg_len := byte(len(data) * 8)
  ret := make([]byte, MSGBLKSIZE256)

  for i, d := range data {
    ret[i] = byte(d)
  }
  ret = append(ret, 0x80)

  for ;len(ret)*8+1+int(msg_len) < 448 && 0 != (len(ret)*8) % 512; {
    ret = append(ret, 0x0)
  }
  // TODO add length
  ret[len(ret)-1] = ret[len(ret)-1] | msg_len
  return ret
}

func compute(M []byte) []uint32 {
  var (
    Hinit = make([]uint32, len(H))
    a, b, c, d, e, f, g, h, t1, t2 uint32
    N = uint32(MSGBLKSIZE256)
    W = make([]uint32, MSGBLKSIZE256)
  )

  for i, d := range H {
    Hinit[i] = d
  }

  for i := uint32(1); i < N; i++ {

    // Prepare the message schedule W
    for t := uint32(0); t < 16; t++ {
      W[t] = uint32(M[t])
    }
    for t := uint32(16); t < 64; t++ {
      W[t] = ssig1(W[t-2]) + W[t-7] + ssig0(t-15) + W[t-16]
    }
    // Initialize the working variables
    a = Hinit[0]
    b = Hinit[1]
    c = Hinit[2]
    d = Hinit[3]
    e = Hinit[4]
    f = Hinit[5]
    g = Hinit[6]
    h = Hinit[7]
    // Perform the main hash computation
    for t := uint32(0); t < 64; t++ {
      t1 = h + bsig1(e) + ch(e,f,g) + K[t] + W[t]
      t2 = bsig0(a) + maj(a,b,c)
      h = g
      g = f
      f = e
      e = d + t1
      d = c
      c = b
      b = a
      a = t1 + t2
    }
    // Compute the uintermediate hash value H(i)
    Hinit[0] += a
    Hinit[1] += b
    Hinit[2] += c
    Hinit[3] += d
    Hinit[4] += e
    Hinit[5] += f
    Hinit[6] += g
    Hinit[7] += h
   }
   return Hinit
 }

func fill_bytes(data []uint32) []byte {
  ret := make([]byte, len(data)*4)

  fmt.Printf("%x", data)
  fmt.Println()
  for i := uint32(0); i < uint32(len(ret)); i++ {
    ret[i] = byte(data[i>>2] >> 8 * (3-(i & 0x03)))
  }
  return ret
}

func digest(data []byte) []byte {
  pad := padding(data)
  di := compute(pad)
  return fill_bytes(di)
}

func main() {
  var (
    file_path string
  )

  flag.StringVar(&file_path, "f", file_path, "file path")
  flag.Parse()

  data, err := ioutil.ReadFile(file_path)
  if err != nil {
    fmt.Println(err)
    return
  }
  data = []byte("abc")
  res := digest(data)
  fmt.Printf("%x\n", res)
  fmt.Printf("%x\n", sha256.Sum256(data))
}

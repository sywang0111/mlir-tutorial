func.func @test(%a: i32, %b: i32) -> i32 {
  %c = "toy.const"(){value=1 : i32}: () -> i32
  %e = "toy.sub"(%a, %b): (i32, i32) -> i32
  %f = "toy.sub"(%c, %c): (i32, i32) -> i32
  %g = "toy.add"(%e, %f): (i32, i32) -> i32
  func.return %e : i32
}
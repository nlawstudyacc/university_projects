defmodule Derivative do

  def test1() do
    f = {:add,
          {:mul,
            {:num, 2},
            {:var, :x}
          },
          {:num, 4}
        }
    d = derive(f, :x)
    s = simplify(d)
    IO.write("expression: #{pprint(f)}\n")
    IO.write("derivative: #{pprint(d)}\n")
    IO.write("simplified: #{pprint(s)}\n")
  end

  def test2() do
    f = {:add,
          {:mul,
            {:num, 2},
            {:mul,
              {:var, :x},
              {:var, :x}
            }
          },
          {:add,
            {:mul,
              {:num, 4},
              {:var, :x}
            },
            {:num, 5}
          }
        }
    d = derive(f, :x)
    s = simplify(d)
    IO.write("expression: #{pprint(f)}\n")
    IO.write("derivative: #{pprint(d)}\n")
    IO.write("simplified: #{pprint(s)}\n")
  end

  def test3() do
    f = {:add,
          {:mul,
            {:num, 2},
            {:exp,
              {:var, :x},
              {:num, 2}
            }
          },
          {:add,
            {:mul,
              {:num, 4},
              {:var, :x}
            },
            {:num, 5}
          }
        }
    d = derive(f, :x)
    s = simplify(d)
    IO.write("expression: #{pprint(f)}\n")
    IO.write("derivative: #{pprint(d)}\n")
    IO.write("simplified: #{pprint(s)}\n")
  end

  def test4() do
    f = {:add,
          {:mul,
            {:num, 2},
            {:mul,
              {:var, :x},
              {:var, :x}
            }
          },
          {:add,
            {:mul,
              {:num, 4},
              {:var, :x}
            },
            {:num, 5}
          }
        }
    d = derive(f, :x)
    c = calculate(d, :x, 5)
    s = simplify(c)
    IO.write("expression: #{pprint(f)}\n")
    IO.write("derivative: #{pprint(d)}\n")
    IO.write("calculated derivative: #{pprint(c)}\n")
    IO.write("simplified: #{pprint(s)}\n")
  end

  def test5() do
    f = {:add,
          {:mul,
            {:num, 2},
            {:mul,
              {:var, :x},
              {:var, :x}
            }
          },
          {:add,
            {:mul,
              {:num, 4},
              {:var, :x}
            },
            {:num, 5}
          }
        }
    d = derive(f, :x)
    c = calculate(d, :x, 4)
    s = simplify(c)
    IO.write("expression: #{pprint(f)}\n")
    IO.write("derivative: #{pprint(d)}\n")
    IO.write("calculated derivative: #{pprint(c)}\n")
    IO.write("simplified: #{pprint(s)}\n")
  end

  def pprint({:num, n}) do "#{n}" end
  def pprint({:var, v}) do "#{v}" end
  def pprint({:add, f1, f2}) do
    "(#{pprint(f1)} + #{pprint(f2)})"
  end
  def pprint({:mul, f1, f2}) do
    "#{pprint(f1)} * #{pprint(f2)}"
  end
  def pprint({:exp, f1, f2}) do
    "#{pprint(f1)}^(#{pprint(f2)})"
  end

  def calculate({:num, n}, _, _) do {:num, n} end
  def calculate({:var, v}, v, n) do {:num, n} end
  def calculate({:var, v}, _, _) do {:var, v} end
  def calculate({:add, f1, f2}, v, n) do
    {:add, calculate(f1, v, n), calculate(f2, v, n)}
  end
  def calculate({:mul, f1, f2}, v, n) do
    {:mul, calculate(f1, v, n), calculate(f2, v, n)}
  end
  def calculate({:exp, f, {:num, n}}, v, c) do
      {:exp, calculate(f, v, c), {:num, n}}
  end

  def derive({:num, _}, _) do {:num, 0} end
  def derive({:var, v}, v) do {:num, 1} end
  def derive({:var, _}, _) do {:num, 0} end
  def derive({:add, f1, f2}, v) do
    {:add, derive(f1, v), derive(f2, v)}
  end
  def derive({:mul, f1, f2}, v) do
    {:add,
      {:mul, derive(f1, v), f2},
      {:mul, f1, derive(f2, v)}
    }
  end
  def derive({:exp, f1, {:num, n}}, v) do
    {:mul,
      {:mul, {:num, n}, {:exp, f1, {:num, n-1}}},
      derive(f1, v)
    }
  end

  def simplify({:exp, f1, f2}) do
    simplify_exp(simplify(f1), simplify(f2))
  end

  def simplify({:num, n}) do {:num, n} end

  def simplify({:var, v}) do {:var, v} end

  def simplify({:add, f1, f2}) do
    simplify_add(simplify(f1),simplify(f2))
  end

  def simplify({:mul, f1, f2}) do
    simplify_mul(simplify(f1),simplify(f2))
  end

  def simplify_exp(f, {:num, 1}) do f end
  def simplify_exp(_, {:num, 0}) do {:num, 1} end
  def simplify_exp({:num, 0}, _) do {:num, 0} end
  def simplify_exp({:num, 1}, _) do {:num, 1} end
  def simplify_exp({:num, n1}, {:num, n2}) do {:num, :math.pow(n1, n2)} end
  def simplify_exp(f1, f2) do {:exp, f1, f2} end

  def simplify_add({:num, 0}, f2) do f2 end
  def simplify_add(f1, {:num, 0}) do f1 end
  def simplify_add({:num, n1}, {:num, n2}) do {:num, n1+n2} end
  def simplify_add(f1, f2) do {:add, f1, f2} end

  def simplify_mul({:num, 1}, f2) do f2 end
  def simplify_mul(f1, {:num, 1}) do f1 end
  def simplify_mul({:num, 0}, _) do {:num, 0} end
  def simplify_mul(_, {:num, 0}) do {:num, 0} end
  def simplify_mul({:num, n1}, {:num, n2}) do {:num, n1*n2} end

  def simplify_mul({:num, n1}, {:mul, {:num, n2}, f}) do {:mul, {:num, n1 * n2}, f} end
  def simplify_mul({:num, n1}, {:mul, f, {:num, n2}}) do {:mul, {:num, n1 * n2}, f} end
  def simplify_mul({:mul, {:num, n2}, f}, {:num, n1}) do {:mul, {:num, n1 * n2}, f} end
  def simplify_mul({:mul, f, {:num, n2}}, {:num, n1}) do {:mul, {:num, n1 * n2}, f} end

  def simplify_mul(f1, f2) do {:mul, f1, f2} end
end

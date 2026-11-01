defmodule Evaluation do
  import EnvList

  def eval({:q, num1, num2}, _env) do {:q, num1, num2} end
  def eval({:num, n}, _env) do {:num, n} end
  def eval({:var, var}, env) do EnvList.lookup(env, var) end
  def eval({:add, e1, e2}, env) do
    add(eval(e1, env), eval(e2, env))
  end
  def eval({:mul, e1, e2}, env) do
    mul(eval(e1, env), eval(e2, env))
  end

  def add({:num, n1}, {:num, n2}) do {:num, n1+n2} end
  def add({:num, n1}, {:q, n, d}) do {:q, (n1 * d + n), d} end
  def add({:q, n, d}, {:num, n1}) do {:q, (n1 * d + n), d} end
  def add({:q, n1, d1}, {:q, n2, d2}) do
    gcd = Integer.gcd(d1, d2)
    {:q, n1 * div(d2, gcd) + n2 * div(d1, gcd) , div(d1 * d2, gcd)}
  end

  def mul({:num, n1}, {:num, n2}) do {:num, n1*n2} end
  def mul({:num, n1}, {:q, n, d}) do
    gcd = Integer.gcd(n1 * n, d)
    {:q, div(n1 * n, gcd), div(d, gcd)}
  end
  def mul({:q, n, d}, {:num, n1}) do
    gcd = Integer.gcd(n1 * n, d)
    {:q, div(n1 * n, gcd), div(d, gcd)}
  end
  def mul({:q, n1, d1}, {:q, n2, d2}) do
    gcd = Integer.gcd(n1 * n2, d1 * d2)
    {:q, div(n1 * n2, gcd), div(d1 * d2, gcd)}
  end
end

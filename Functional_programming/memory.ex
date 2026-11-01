defmodule Memory do
  def new() do %{} end
  def add(mem, key, value) do Map.put(mem, key, value) end
  def lookup(mem, key) do Map.get(mem, key) end
end

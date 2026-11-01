defmodule Graph do
  def lookup([], _) do
    :error
  end
  def lookup([{nameOfNodeToFind, rate, neighbours}|_], nameOfNodeToFind) do
    {nameOfNodeToFind, rate, neighbours}
  end
  def lookup([_|tailNodes], nameOfNodeToFind) do
    lookup(tailNodes, nameOfNodeToFind)
  end

  def delete(graph, nameOfNodeToDelete) do
    delete(graph, nameOfNodeToDelete, [])
  end
  def delete([], _, _) do
    :error
  end
  def delete([{nameOfNodeToDelete, _, _}|tailNodes], nameOfNodeToDelete, resultGraph) do
    Enum.reverse(resultGraph) ++ tailNodes
  end
  def delete([headNode|tailNodes], nameOfNodeToDelete, resultGraph) do
    delete(tailNodes, nameOfNodeToDelete, [headNode|resultGraph])
  end
end

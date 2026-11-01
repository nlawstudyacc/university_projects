defmodule Train do
  def take(_, 0) do
    []
  end
  def take([headWagon|tailWagons], n) do
    [headWagon|take(tailWagons, n - 1)]
  end

  def drop(wagons, 0) do
    wagons
  end
  def drop([_|tailWagons], n) do
    drop(tailWagons, n - 1)
  end

  def append([], train2) do
    train2
  end
  def append([headWagon|tailWagons],train2) do
    [headWagon|append(tailWagons, train2)]
  end

  def member([], _) do
    false
  end
  def member([foundWagon|_tailWagons], foundWagon) do
    true
  end
  def member([_headWagon|tailWagons], y) do
    member(tailWagons, y)
  end

  def position([foundWagon|_tailWagons], foundWagon) do
    1
  end
  def position([_headWagon|tailWagons], y) do
    1 + position(tailWagons, y)
  end

  def split([foundWagon|tailWagons], foundWagon) do
    {[], tailWagons}
  end
  def split([headWagon|tailWagons], y) do
    {beforeSplitWagons, afterSplitWagons} = split(tailWagons, y)
    {[headWagon|beforeSplitWagons], afterSplitWagons}
  end

  def main([], n) do
    {n, [], []}
  end
  def main([headWagon|tailWagons], n) do
    case main(tailWagons, n) do
      {0, remain, take} ->
        {0, [headWagon|remain], take}
      {k, remain, take} ->
        {k - 1, remain, [headWagon|take]}
    end
  end
end

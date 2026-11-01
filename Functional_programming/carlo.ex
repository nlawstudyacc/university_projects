defmodule Carlo do
  def dart(radius) do
    x = Enum.random(0..radius)
    y = Enum.random(0..radius)
    :math.pow(radius, 2) > :math.pow(x, 2) + :math.pow(y, 2)
  end

  def round(0, _, accumulatedValue) do
    accumulatedValue
  end
  def round(numberOfRounds, radius, accumulatedValue) do
    if dart(radius) do
      round(numberOfRounds - 1, radius, accumulatedValue + 1)
    else
      round(numberOfRounds - 1, radius, accumulatedValue)
    end
  end

  def rounds(numberOfTrials, numberOfRounds, radius) do
    rounds(numberOfTrials, numberOfRounds, 0, radius, 0)
  end

  def rounds(0, _, totalNumberOfRounds, _, accumulatedResult) do
    gcd = Integer.gcd(accumulatedResult, totalNumberOfRounds)
    :io.format("The resulting fraction is: ~w/~w = ~f", [accumulatedResult/gcd, totalNumberOfRounds/gcd, 4 * accumulatedResult/totalNumberOfRounds])
  end
  def rounds(numberOfTrials, numberOfRounds, totalNumberOfRounds, radius, accumulatedResult) do
    accumulatedResult = round(numberOfRounds, radius, accumulatedResult)
    totalNumberOfRounds = totalNumberOfRounds + numberOfRounds
    pi = 4 * accumulatedResult / totalNumberOfRounds
    :io.format("The difference between the computed pi value [~f] and the real one is: ~f\n", [pi, (pi - :math.pi())])
    rounds(numberOfTrials-1, numberOfRounds, totalNumberOfRounds, radius, accumulatedResult)
  end
end

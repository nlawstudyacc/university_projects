defmodule Day_16 do
  #Day_16.execute("C:/Users/nicho/Desktop/KTH/Programming_II/Day_16.txt")
  def execute(pathToFile) do
    {:ok, fileContents} = File.read(pathToFile)
    buffer = String.split(fileContents, "\n")
    completeGraph = constructGraph(buffer)
    reducedGraph = reconstructGraph(completeGraph) |> reducePaths(completeGraph)
    runTask(reducedGraph)
  end

  def runTask(graph) do
    filtered_list = Enum.reject(graph, fn {:AA, _, _} -> true; _ -> false end)
    closedValves = Enum.map(filtered_list, &elem(&1, 0))
    memory = Map.new
    {largestPressure, _} = findLargestPressure({30, :AA, []}, closedValves, graph, 0, memory)
    largestPressure
  end
  #information -> {timeRemaining, currentValve, openValves}
  #map lookup shall return total pressure together with the path taken: in this case just nodes traversal [:AA, :BB, :CC, :DD, :AA] is an example
  #findLargersPressure({timeRemaining, currentValve, openedValves}, closedValves, graph, rateCollected, memory)
  def findLargestPressure({0, _, _}, _, _, _, memory) do
    #why bother calculating with 0?
    {0, memory}
  end
  def findLargestPressure({timeRemaining, _, _} = keyInformation, [], _, rateCollected, memory) do
    #gives me the pressure that is computed via multiplying all of the pressure rate gathered from previous calls and time that is left
    pressureFound = rateCollected * timeRemaining
    memory = Map.put(memory, keyInformation, pressureFound)
    {pressureFound, memory}
  end
  def findLargestPressure(keyInformation, closedValves, graph, rateCollected, memory) do
    case Map.get(memory, keyInformation) do
      nil ->
	      {largestPressure, memory} = exploreRoute(keyInformation, closedValves, graph, rateCollected, memory)
	      memory = Map.put(memory, keyInformation, largestPressure)
	      {largestPressure, memory}
      largestPressure ->
	      {largestPressure, memory}
    end
  end

  def exploreRoute({timeRemaining, currentValve, openedValves}, closedValves, graph, rateCollected, memory) do

    {_, rateInValve, neighbourValves} = Graph.lookup(graph, currentValve)
    {largePressure1, memory} = if Enum.member?(closedValves, currentValve) do
      updatedClosedValves = List.delete(closedValves, currentValve)
      {largePressure1, memory} = findLargestPressure({timeRemaining - 1, currentValve, insertIntoOpened(openedValves, currentValve)}, updatedClosedValves, graph, rateCollected + rateInValve, memory)
      #one minute on opening a valve still allows pressure to get released
      largePressure1 = largePressure1 + rateCollected
      {largePressure1, memory}
    else
      {rateCollected * timeRemaining, memory}
    end

    Enum.reduce(neighbourValves, {largePressure1, memory},
      fn({valveAnalyzed, timeToReach}, {largePressure1, memory}) ->
        if (timeToReach < timeRemaining) do
	        {largePressure2, memory} = findLargestPressure({timeRemaining - timeToReach, valveAnalyzed, openedValves}, closedValves, graph, rateCollected, memory)
	        #while we are travelling to next valve the pressure still gets released so we just times it by time to reach the valve
          largePressure2 = largePressure2 + (rateCollected * timeToReach)
	        if (largePressure2 > largePressure1) do
	          {largePressure2, memory}
	        else
	          {largePressure1, memory}
	        end
	      else
          #we cannot even reach the neighbour valve
	        {largePressure1, memory}
	      end
      end)
  end


  #we have to sustain order somehow otherwise there will be too many possbile combinations
  def insertIntoOpened([], valve) do [valve] end
  def insertIntoOpened([valveName|otherValves], valveToInsert) when valveName < valveToInsert do  [valveName|insertIntoOpened(otherValves, valveToInsert)] end
  def insertIntoOpened(opened, valveToInsert) do  [valveToInsert|opened] end

  def reducePaths(reducedGraph, completeGraph) do
    reducePaths(reducedGraph, completeGraph, [])
  end
  def reducePaths([], _, result) do
    Enum.reverse(result)
  end
  def reducePaths([{valveName, rate, neighbourValves}|tailNodes], completeGraph, result) do
    headNode = {valveName, rate, List.flatten(Enum.map(neighbourValves, fn(valve) ->
      findPaths(valve, completeGraph, 1, 30, valveName) end))}
    reducePaths(tailNodes, completeGraph, [headNode|result])
  end

  def findPaths(_, _, _, -1, _) do
    []
  end
  def findPaths({valveTo, _}, completeGraph, timeToReach, timeRemaining, valveFrom) do
    case {valveTo, _, neighbourValves} = Graph.lookup(completeGraph, valveTo) do
      {:AA, _, _} -> {valveTo, timeToReach}
      {_, 0, _} -> Enum.map(neighbourValves, fn(valve) ->
        case valve do
          {^valveFrom, _} -> []
          _ -> findPaths(valve, completeGraph, timeToReach + 1, timeRemaining - 1, valveTo)
        end
      end)
      _ -> {valveTo, timeToReach}
    end
  end

  def reconstructGraph(graph) do
    reconstructGraph(graph, [])
  end
  def reconstructGraph([], resultGraph) do
    Enum.reverse(resultGraph)
  end
  def reconstructGraph([{:AA, _, _} = headNode|remainingNodes], resultGraph) do
    reconstructGraph(remainingNodes, [headNode|resultGraph])
  end
  def reconstructGraph([{_, rate, _} = headNode|remainingNodes], resultGraph) do
    case rate do
      0 -> reconstructGraph(remainingNodes, resultGraph)
      _ ->
        reconstructGraph(remainingNodes, [headNode|resultGraph])
    end
  end

  def constructGraph(input) do
    Enum.map(processInformation(input), fn(tupleToAnalyze) -> setTimes(tupleToAnalyze) end)
  end

  def setTimes({valve, rate, valves}) do
    {valve, rate, Enum.map(valves, fn(neighbourValve) -> {neighbourValve, 1} end)}
  end

  def processInformation(list) do
    Enum.map(list, fn(data) -> processingFunction(data) end)
  end

  def processingFunction(data) do
    [valveNameProcessing, pressureRate, neighbourValvesProcessing] = String.split(data, ["=", ";"])
    {getValveName(valveNameProcessing), String.to_integer(pressureRate), getNeighbourValveNames(neighbourValvesProcessing)}
  end

  def getValveName(valveNameProcessing) do
    valveNameProcessing = String.split(valveNameProcessing, " ")
    [_|[valveName, _, _, _]] = valveNameProcessing
    String.to_atom(valveName)
  end

  def getNeighbourValveNames(neighbourValvesProcessing) do
    [_, neighbourValvesProcessing] = String.split(neighbourValvesProcessing, [" tunnels lead to valves ", " tunnel leads to valve "])
    Enum.map(String.split(neighbourValvesProcessing, ", "), fn (string) -> String.to_atom(string) end)
  end

  def test() do
    ["Valve AA has flow rate=0; tunnels lead to valves DD, II, BB",
     "Valve BB has flow rate=13; tunnels lead to valves CC, AA",
     "Valve CC has flow rate=2; tunnels lead to valves DD, BB",
     "Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE",
     "Valve EE has flow rate=3; tunnels lead to valves FF, DD",
     "Valve FF has flow rate=0; tunnels lead to valves EE, GG",
     "Valve GG has flow rate=0; tunnels lead to valves FF, HH",
     "Valve HH has flow rate=22; tunnel leads to valve GG",
     "Valve II has flow rate=0; tunnels lead to valves AA, JJ",
     "Valve JJ has flow rate=21; tunnel leads to valve II"]
  end
end

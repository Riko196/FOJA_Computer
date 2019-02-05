export const callBackendAPI = async (grammarString, request) => {
  const response = await fetch(
    `http://localhost:8080/grammarRequest/${grammarString}/${request}`,
    {
      method: "GET",
      headers: {
        Accept: "application/json"
      }
    }
  );

  const body = await response.text();
  if (response.status !== 200) {
    throw Error(body.message);
  }
  return body;
};

export const callBackendAPIEquivalence = async (
  grammarString1,
  grammarString2,
  request
) => {
  const response = await fetch(
    `http://localhost:8080/grammarRequest/${grammarString1}/${grammarString2}/${request}`,
    {
      method: "GET",
      headers: {
        Accept: "application/json"
      }
    }
  );
  const body = await response.text();
  if (response.status !== 200) {
    throw Error(body.message);
  }
  return body;
};
